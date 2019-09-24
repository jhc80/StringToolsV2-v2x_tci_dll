require("common");
require("user");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

local lex_xx = LexerCpp.new();
local lex = lex_xx:Lexer();

lex:LoadFile(mem_text_file);

local mf,mf_file = new_memfile();

while not lex:IsEnd() do
    local type = lex_xx:NextToken(mf_file);        
    local cur_token = mf_file;
    
    if type ~= TOKEN_MULTI_LINE_COMMENTS and type ~= TOKEN_SINGLE_LINE_COMMENTS then
        print_whole_file(mf_file);
    end
end

