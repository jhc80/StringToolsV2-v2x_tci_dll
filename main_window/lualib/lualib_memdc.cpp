#include "lualib_memdc.h"
#include "mem_tool.h"
#include "syslog.h"
#include "lualib_filebase.h"
#include "lualib_luahdc.h"
#include "encoder.h"
#include "lua_helper.h"

static status_t memdc_drawrect_v2(lua_State *L);
static status_t memdc_drawrect_v3(lua_State *L);
static status_t memdc_drawrect_v4(lua_State *L);

static bool memdc_is_userdata_valid(lua_userdata *ud)
{
    if(ud == NULL)return false;
    if(ud->p == NULL)return false;
    if(ud->__weak_ref_id == 0) return false;
    CMemDC *p = (CMemDC*)ud->p;
    return p->__weak_ref_id == ud->__weak_ref_id;
}    

bool is_memdc(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_MEMDC,
    };            
    lua_userdata *ud = NULL;
    for(size_t i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return memdc_is_userdata_valid(ud);  
}

CMemDC *get_memdc(lua_State *L, int idx)
{
    lua_userdata *ud = NULL;
    if(is_memdc(L,idx))
    {
        ud = (lua_userdata*)lua_touserdata(L,idx);		
    }
    ASSERT(ud);
    return (CMemDC *)ud->p;
} 

lua_userdata *memdc_new_userdata(lua_State *L,CMemDC *pobj,int is_weak)
{
    lua_userdata *ud = (lua_userdata*)lua_newuserdata(L,sizeof(lua_userdata));
    ASSERT(ud && pobj);
    ud->p = pobj;
    ud->is_attached = is_weak;
    ud->__weak_ref_id = pobj->__weak_ref_id;
    luaL_getmetatable(L,LUA_USERDATA_MEMDC);
    lua_setmetatable(L,-2);
    return ud;
}

static int memdc_gc_(lua_State *L)
{
    if(!is_memdc(L,1)) return 0;

    lua_userdata *ud = (lua_userdata*)lua_touserdata(L,1);		
    ASSERT(ud);

    if(!(ud->is_attached))
    {
        CMemDC *pmemdc = (CMemDC*)ud->p;
        DEL(pmemdc);
    }
    return 0;
}

static int memdc_issame_(lua_State *L)
{
    CMemDC *pmemdc1 = get_memdc(L,1);
    ASSERT(pmemdc1);
    CMemDC *pmemdc2 = get_memdc(L,2);
    ASSERT(pmemdc2);
    int is_same = (pmemdc1==pmemdc2);
    lua_pushboolean(L,is_same);
    return 1;
}

static int memdc_tostring_(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    char buf[1024];
    sprintf(buf,"userdata:memdc:%p",pmemdc);
    lua_pushstring(L,buf);
    return 1;
}

/****************************************************/
static status_t memdc_new(lua_State *L)
{
    CMemDC *pmemdc;
    NEW(pmemdc,CMemDC);
    pmemdc->Init();
    memdc_new_userdata(L,pmemdc,0);
    return 1;
}

static status_t memdc_drawrect_v1(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int r[1024];
    int r_len = 1024;
    CLuaVm::ToIntArray(L,2,r,&r_len);
	ASSERT(r_len == 4);
    uint32_t color = (uint32_t)lua_tointeger(L,3);

	RECT t;
	t.left = r[0];
	t.top = r[1];
	t.right = r[2];
	t.bottom = r[3];

    int ret0 = pmemdc->DrawRect(t,color);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_drawrect(lua_State *L)
{
    if(lua_isinteger(L,3))
    {
        return memdc_drawrect_v1(L);
    }

    if(lua_isinteger(L,2))
    {
        return memdc_drawrect_v2(L);
    }

    if(lua_isinteger(L,2) && lua_isinteger(L,3) && lua_isinteger(L,4) && lua_isinteger(L,5) && lua_isinteger(L,6))
    {
        return memdc_drawrect_v3(L);
    }

    if(lua_isinteger(L,2) && lua_isinteger(L,3) && lua_isinteger(L,4) && lua_isinteger(L,5))
    {
        return memdc_drawrect_v4(L);
    }

    return 0;
}

static status_t memdc_createbitmap(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int w = (int)lua_tointeger(L,2);
    int h = (int)lua_tointeger(L,3);
    int bits = (int)lua_tointeger(L,4);
	if(bits==0)bits=24;
    status_t ret0 = pmemdc->CreateBitmap(w,h,bits);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_loadbitmap(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    CFileBase *file = get_filebase(L,2);
    ASSERT(file);
    status_t ret0 = pmemdc->LoadBitMap(file);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_savebmp(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    CFileBase *file = get_filebase(L,2);
    ASSERT(file);
    int bits = (int)lua_tointeger(L,3);
	if(bits == 0)bits = 24;
    status_t ret0 = pmemdc->SaveBmp(file,bits);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_setbrush(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    uint32_t style = (uint32_t)lua_tointeger(L,2);
    uint32_t color = (uint32_t)lua_tointeger(L,3);
    uint32_t hatch = (uint32_t)lua_tointeger(L,4);
    status_t ret0 = pmemdc->SetBrush(style,color,hatch);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_updateparent(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    status_t ret0 = pmemdc->UpdateParent();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_settransparentbkmode(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    status_t ret0 = pmemdc->SetTransparentBkMode();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_attachdc(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    CLuaHdc *hdc = get_luahdc(L,2);
    ASSERT(hdc);
    status_t ret0 = pmemdc->AttachDC(hdc->hdc);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_getpixel(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int x = (int)lua_tointeger(L,2);
    int y = (int)lua_tointeger(L,3);
    uint32_t ret0 = pmemdc->GetPixel(x,y);
    lua_pushinteger(L,ret0);
    return 1;
}

static status_t memdc_setstockfont(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int fnobject = (int)lua_tointeger(L,2);
    status_t ret0 = pmemdc->SetStockFont(fnobject);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_settextcolor(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    uint32_t color = (uint32_t)lua_tointeger(L,2);
    status_t ret0 = pmemdc->SetTextColor(color);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_settextbkcolor(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    uint32_t color = (uint32_t)lua_tointeger(L,2);
    status_t ret0 = pmemdc->SetTextBkColor(color);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_setpen(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int fnpenstyle = (int)lua_tointeger(L,2);
    int nwidth = (int)lua_tointeger(L,3);
    uint32_t crcolor = (uint32_t)lua_tointeger(L,4);
    status_t ret0 = pmemdc->SetPen(fnpenstyle,nwidth,crcolor);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_sethatchbrush(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int fnstyle = (int)lua_tointeger(L,2);
    uint32_t clrref = (uint32_t)lua_tointeger(L,3);
    status_t ret0 = pmemdc->SetHatchBrush(fnstyle,clrref);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_setsolidbrush(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    uint32_t clrref = (uint32_t)lua_tointeger(L,2);
    status_t ret0 = pmemdc->SetSolidBrush(clrref);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_textout(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int x = (int)lua_tointeger(L,2);
    int y = (int)lua_tointeger(L,3);

	LUA_TO_UNICODE_STRING(str,L,4);

    status_t ret0 = pmemdc->TextOut(x,y,str);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_textoutex(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int x = (int)lua_tointeger(L,2);
    int y = (int)lua_tointeger(L,3);
    int r[1024];
    int r_len = 1024;
    CLuaVm::ToIntArray(L,4,r,&r_len);
    
	LUA_TO_UNICODE_STRING(str,L,5);

	RECT t;
	t.left = r[0];
	t.top = r[1];
	t.right = r[2];
	t.bottom = r[3];

    int ret0 = pmemdc->TextOutEx(x,y,&t,str);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_fillrect(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int l = (int)lua_tointeger(L,2);
    int t = (int)lua_tointeger(L,3);
    int w = (int)lua_tointeger(L,4);
    int h = (int)lua_tointeger(L,5);
    status_t ret0 = pmemdc->FillRect(l,t,w,h);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_drawrect_v2(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    uint32_t color = (uint32_t)lua_tointeger(L,2);
    status_t ret0 = pmemdc->DrawRect(color);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_drawrect_v3(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int l = (int)lua_tointeger(L,2);
    int t = (int)lua_tointeger(L,3);
    int w = (int)lua_tointeger(L,4);
    int h = (int)lua_tointeger(L,5);
    uint32_t color = (uint32_t)lua_tointeger(L,6);
    status_t ret0 = pmemdc->DrawRect(l,t,w,h,color);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_drawrect_v4(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int l = (int)lua_tointeger(L,2);
    int t = (int)lua_tointeger(L,3);
    int w = (int)lua_tointeger(L,4);
    int h = (int)lua_tointeger(L,5);
    status_t ret0 = pmemdc->DrawRect(l,t,w,h);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_lineto(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int x = (int)lua_tointeger(L,2);
    int y = (int)lua_tointeger(L,3);
    status_t ret0 = pmemdc->LineTo(x,y);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_ellipse(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int l = (int)lua_tointeger(L,2);
    int t = (int)lua_tointeger(L,3);
    int r = (int)lua_tointeger(L,4);
    int b = (int)lua_tointeger(L,5);
    status_t ret0 = pmemdc->Ellipse(l,t,r,b);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_arc(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int nleftrect = (int)lua_tointeger(L,2);
    int ntoprect = (int)lua_tointeger(L,3);
    int nrightrect = (int)lua_tointeger(L,4);
    int nbottomrect = (int)lua_tointeger(L,5);
    int nxradial1 = (int)lua_tointeger(L,6);
    int nyradial1 = (int)lua_tointeger(L,7);
    int nxradial2 = (int)lua_tointeger(L,8);
    int nyradial2 = (int)lua_tointeger(L,9);
    status_t ret0 = pmemdc->Arc(nleftrect,ntoprect,nrightrect,nbottomrect,nxradial1,nyradial1,nxradial2,nyradial2);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_moveto(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int x = (int)lua_tointeger(L,2);
    int y = (int)lua_tointeger(L,3);
    status_t ret0 = pmemdc->MoveTo(x,y);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_drawtoscreen(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    status_t ret0 = pmemdc->DrawToScreen();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_clear(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    status_t ret0 = pmemdc->Clear();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_stretchtodc(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    CLuaHdc *hdc_des = get_luahdc(L,2);
    ASSERT(hdc_des);
    int width = (int)lua_tointeger(L,3);
    int height = (int)lua_tointeger(L,4);
    status_t ret0 = pmemdc->StretchToDC(hdc_des->hdc,width,height);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_setwindowposx(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int x = (int)lua_tointeger(L,2);
    status_t ret0 = pmemdc->SetWindowPosX(x);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_setwindowposy(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int y = (int)lua_tointeger(L,2);
    status_t ret0 = pmemdc->SetWindowPosY(y);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_setpixel(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int x = (int)lua_tointeger(L,2);
    int y = (int)lua_tointeger(L,3);
    uint32_t color = (uint32_t)lua_tointeger(L,4);
    status_t ret0 = pmemdc->SetPixel(x,y,color);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_copy(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    CLuaHdc *hdc_src = get_luahdc(L,2);
    ASSERT(hdc_src);
    status_t ret0 = pmemdc->Copy(hdc_src->hdc);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_paste(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    CLuaHdc *hdc_des = get_luahdc(L,2);
    ASSERT(hdc_des);
    status_t ret0 = pmemdc->Paste(hdc_des->hdc);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_setparent(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    HWND hp = (HWND)lua_tointeger(L,2);
    status_t ret0 = pmemdc->SetParent(hp);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_setpos(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int l = (int)lua_tointeger(L,2);
    int t = (int)lua_tointeger(L,3);
    status_t ret0 = pmemdc->SetPos(l,t);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_createcompatibledc(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    CLuaHdc *hdc = get_luahdc(L,2);
    ASSERT(hdc);
    int ret0 = pmemdc->CreateCompatibleDC(hdc->hdc);
    lua_pushinteger(L,ret0);
    return 1;
}

static status_t memdc_drawtext(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    
	LUA_TO_UNICODE_STRING(str,L,2);

    int r[1024];
    int r_len = 1024;
    CLuaVm::ToIntArray(L,3,r,&r_len);

	RECT t;
	t.left = r[0];
	t.top = r[1];
	t.right = r[2];
	t.bottom = r[3];

    uint32_t dwdtformat = (uint32_t)lua_tointeger(L,4);
    int ret0 = pmemdc->DrawText(str,&t,dwdtformat);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t memdc_getwidth(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int ret0 = pmemdc->width;
    lua_pushinteger(L,ret0);
    return 1;
}

static status_t memdc_getheight(lua_State *L)
{
    CMemDC *pmemdc = get_memdc(L,1);
    ASSERT(pmemdc);
    int ret0 = pmemdc->height;
    lua_pushinteger(L,ret0);
    return 1;
}

/****************************************************/
static const luaL_Reg memdc_funcs_[] = {
    {"__gc",memdc_gc_},
    {"__tostring",memdc_tostring_},
    {"__is_same",memdc_issame_},
    {"new",memdc_new},
    {"DrawRect",memdc_drawrect},
    {"CreateBitmap",memdc_createbitmap},
    {"LoadBitMap",memdc_loadbitmap},
    {"SaveBmp",memdc_savebmp},
    {"SetBrush",memdc_setbrush},
    {"UpdateParent",memdc_updateparent},
    {"SetTransparentBkMode",memdc_settransparentbkmode},
    {"AttachDC",memdc_attachdc},
    {"GetPixel",memdc_getpixel},
    {"SetStockFont",memdc_setstockfont},
    {"SetTextColor",memdc_settextcolor},
    {"SetTextBkColor",memdc_settextbkcolor},
    {"SetPen",memdc_setpen},
    {"SetHatchBrush",memdc_sethatchbrush},
    {"SetSolidBrush",memdc_setsolidbrush},
    {"TextOut",memdc_textout},
    {"TextOutEx",memdc_textoutex},
    {"FillRect",memdc_fillrect},
    {"LineTo",memdc_lineto},
    {"Ellipse",memdc_ellipse},
    {"Arc",memdc_arc},
    {"MoveTo",memdc_moveto},
    {"DrawToScreen",memdc_drawtoscreen},
    {"Clear",memdc_clear},
    {"StretchToDC",memdc_stretchtodc},
    {"SetWindowPosX",memdc_setwindowposx},
    {"SetWindowPosY",memdc_setwindowposy},
    {"SetPixel",memdc_setpixel},
    {"Copy",memdc_copy},
    {"Paste",memdc_paste},
    {"SetParent",memdc_setparent},
    {"SetPos",memdc_setpos},
    {"CreateCompatibleDC",memdc_createcompatibledc},
    {"DrawText",memdc_drawtext},	
    {"GetWidth",memdc_getwidth},
    {"GetHeight",memdc_getheight},
    {NULL,NULL},
};

const luaL_Reg* get_memdc_funcs()
{
    return memdc_funcs_;
}

static int luaL_register_memdc(lua_State *L)
{	
    static luaL_Reg _memdc_funcs_[MAX_LUA_FUNCS];
    int _index = 0;        

    CLuaVm::CombineLuaFuncTable(_memdc_funcs_,&_index,get_memdc_funcs(),true);

    luaL_newmetatable(L, LUA_USERDATA_MEMDC);
    lua_pushvalue(L, -1);	
    lua_setfield(L, -2, "__index");	
    luaL_setfuncs(L,_memdc_funcs_,0);	
    lua_pop(L, 1);
    luaL_newlib(L,_memdc_funcs_);
    return 1;
}        

int luaopen_memdc(lua_State *L)
{
    luaL_requiref(L, "MemDC",luaL_register_memdc,1);
    lua_pop(L, 1);
    return 0;
}        

