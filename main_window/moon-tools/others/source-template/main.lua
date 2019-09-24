require("common");
require("user");
require("bson");
require("win32");
require("search_engine")

local UI_WND_HEIGHT=80;

App.ClearScreen();
App.StartNet();

App.ShowEmbeddedUIWindow(UI_WND_HEIGHT);
local hwnd = App.GetHWnd(HWND_EMBEDDED_UI);

if not hwnd then
    printnl("can not find embedded ui window");
    return
end

local _,_,UI_WND_WIDTH = Win32.GetClientRect(hwnd);

local editbox = EditBox.new();
editbox:SetParent(hwnd);

editbox:AddStyle(
    ES_MULTILINE |
    WS_VSCROLL|ES_AUTOVSCROLL |
    ES_AUTOHSCROLL|ES_WANTRETURN |
    WS_BORDER
);

editbox:Create();
editbox:SetStockFont(SYSTEM_FIXED_FONT);

function relayout(width,height)
    editbox:MoveWindow(
        10,4,
        width-10,height-10
    );    
end

local search_engine = SearchEngine.new();
search_engine:LoadSourceTemplate(program_language);

function move_to_top()
    local hwnd = App.GetHWnd(HWND_EDIT_BOX);
    Win32.SendMessage(hwnd,EM_SETSEL,0,0);
    Win32.SendMessage(hwnd,EM_SCROLLCARET,0,0);
end

function on_search()
    local text = new_mem();
    editbox:GetText(text);

    App.ClearScreen();
    local res = search_engine:GetMatchResult(text);
    if res then        
        for _,v in ipairs(res) do
            print_whole_file(v.text);
            printnl("########################################################################################");
        end
    end    
    App.WaitBuffer();
    move_to_top();
end

Win32.SetOnWindowMessage(function(hwnd,message,wparam,lparam)
    if hwnd == editbox:GetHWnd() and message == WM_CHAR then
        on_search();
    end
end);

relayout(UI_WND_WIDTH,UI_WND_HEIGHT);
on_search();

App.MainLoop();

