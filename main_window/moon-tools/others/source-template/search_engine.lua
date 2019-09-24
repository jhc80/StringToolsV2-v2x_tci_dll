require("common")

SearchEngine = class();

function SearchEngine:ctor()
    self.m_all_blocks = {};
end

function SearchEngine:LoadSourceTemplate(ext)
    local filename = App.GetSelfPath("template."..ext)
    local source = new_mem(filename);
    self:SplitSourceFile(source);
end

function SearchEngine:IsSplitLine(line)
    line:Seek(0);
    local find = 0;
    while not line:IsEnd() do
        local ch = line:Getc();
        if ch == 35 then --'#'
            find = find + 1;
        else
            return false
        end
    end
    return find > 0;
end

function SearchEngine:SplitSourceFile(source)
    local mem = new_mem();
    local tmp = new_memfile();
    source:Seek(0);

    self.m_all_blocks = {};
    while source:ReadLine(mem) do
        if self:IsSplitLine(mem) then
            if tmp:GetSize() > 0 then
                table.insert(self.m_all_blocks,file_to_mem(tmp));
                tmp = new_memfile();
            end
        else
            tmp:Puts(mem);
            tmp:Puts("\r\n");
        end
    end

    if tmp:GetSize() > 0 then
        table.insert(self.m_all_blocks,file_to_mem(tmp));
    end
end

function SearchEngine:MatchScore_V1(block,mem)
    if mem:GetSize() ==0 then
        return 1;
    end
    
    local word = new_mem();
    mem:Seek(0);
    mem:SetSplitChars("\t \r\n");
        
    local cur_score = 10000;
    local score = 0;
    
    while mem:ReadWord(word) do    
        block:Seek(0);
        if block:SearchStr(word:CStr(),false,false) >= 0 then
            score = score + cur_score;
            cur_score = math.floor(cur_score / 10);
        end    
    end
    return score;
end

function SearchEngine:MatchScore_V2(block,mem)
    if mem:GetSize() ==0 then
        return 1;
    end
    
    local word = new_mem();
    mem:Seek(0);
    mem:SetSplitChars("\t \r\n");
       
    while mem:ReadWord(word) do          
        block:Seek(0);
        if block:SearchStr(word:CStr(),false,false) < 0 then
            return 0;
        end    
    end
    
    return 100;
end

function SearchEngine:GetMatchResult(input_mem)
    local res = {};
    
    input_mem:Trim();

    for _,v in ipairs(self.m_all_blocks) do
        local score = self:MatchScore_V2(v,input_mem);
        if score > 0 then
            table.insert(res,{
                score = score,
                text = v,
            });
        end
    end

    table.sort(res,function(e1,e2)
        return e1.score > e2.score;
    end);
    return #res > 0 and res or nil;
end
