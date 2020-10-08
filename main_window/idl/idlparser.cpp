#include "idlparser.h"
#include "syslog.h"
#include "mem_tool.h"
#include "memfile.h"

CIdlParser::CIdlParser()
{
	this->InitBasic();
}
CIdlParser::~CIdlParser()
{
	this->Destroy();
}
status_t CIdlParser::InitBasic()
{
    WEAK_REF_CLEAR();
	this->m_Lexer.InitBasic();
    m_UncertainError.InitBasic();
    m_CertainError.InitBasic();
	return OK;
}
status_t CIdlParser::Init()
{
	this->InitBasic();
    
	this->m_Lexer.Init();
    this->m_UncertainError.Init();
    m_CertainError.Init();
	return OK;
}
status_t CIdlParser::Destroy()
{
    WEAK_REF_DESTROY();
    m_CertainError.Destroy();
    m_UncertainError.Destroy();
	this->m_Lexer.Destroy();
	this->InitBasic();
	return OK;
}
int CIdlParser::Comp(CIdlParser *_p)
{
	ASSERT(_p);
	if(this==_p)return 0;
	return 0;
}
status_t CIdlParser::Copy(CIdlParser *_p)
{
	ASSERT(_p);
	if(this == _p)return OK;
	this->m_Lexer.Copy(&_p->m_Lexer);
	return OK;
}
status_t CIdlParser::Print(CFileBase *_buf)
{
	_buf->Log("Lexer = {");
	_buf->IncLogLevel(1);
	m_Lexer.Print(_buf);
	_buf->IncLogLevel(-1);
	_buf->Log("}");
	return OK;
}
CIdlLexer* CIdlParser::GetLexer()
{
	return &this->m_Lexer;
}
status_t CIdlParser::SetLexer(CIdlLexer* _lexer)
{
	this->m_Lexer.Copy(_lexer);
	return OK;
}
status_t CIdlParser::LoadSource(const char *idlfile)
{
    ASSERT(idlfile);
    return m_Lexer.LoadSource(idlfile);
}
status_t CIdlParser::LoadSource(CFileBase *file)
{
    ASSERT(file);
    return m_Lexer.LoadSource(file);
}
status_t CIdlParser::CertainError(const char* format, ...)
{
    char buffer [LBUF_SIZE];
    crt_va_list ap;
    crt_va_start(ap, format);
    crt_vsprintf (buffer, format, ap);    
    m_CertainError.Log("syntax error: %s",buffer);
    m_Lexer.ReportError(&m_CertainError);
    m_Lexer.m_ErrorNo = ERR_PARSE_ERROR;
    crt_va_end(ap);
    return OK;
}

status_t CIdlParser::UncertainError(const char* format, ...)
{
    char buffer [LBUF_SIZE];
    crt_va_list ap;
    crt_va_start(ap, format);
    crt_vsprintf (buffer, format, ap);
    m_UncertainError.SetSize(0);
    m_Lexer.ReportError(&m_UncertainError);
    m_UncertainError.Puts(buffer);
    crt_va_end(ap);
    return OK;
}

status_t CIdlParser::ParseAll(CIdlModule *idl_module)
{
    ASSERT(idl_module);

    m_Lexer.Reset();
    
    CIdlClass *idl_class = NULL;

    while(true)
    {    
        if(idl_class == NULL)
        {
            NEW(idl_class,CIdlClass);
            idl_class->Init();
        }
    
        int parsed = 0;

        LOCAL_MEM(hint);
        if(this->ParseHint(&hint))
        {
            ASSERT(idl_class);
            idl_class->AddHint(&hint);
            parsed ++;
        }

        ASSERT(idl_class);
        if(this->ParseClass(idl_class))
        {
            idl_module->AddIdlClass(idl_class);
            idl_class = NULL;
            parsed ++;
        }

        if(!parsed)
        {
            if(!m_Lexer.IsEnd())
            {
                this->CertainError("'class' or '[' expected,but got '%s'",m_Lexer.GetCurValStr());            
            }
            break;
        }
    }

    DEL(idl_class);
    return !m_Lexer.HasError();
}

status_t CIdlParser::ParseHint(CMem *hint)
{
    ASSERT(hint);
    
    IdlLexerContext context;
    status_t parse_ok = ERROR;

    m_Lexer.SaveContext(&context);

    int token = m_Lexer.Next();
    if(token != IDL_TOKEN_LEFT_SQUARE_BRACKETS)
    {
        this->UncertainError("'[' expected");
        m_Lexer.RestoreContext(&context);
        return ERROR;
    }

    while(true)
    {
        token = m_Lexer.NextTokenAll();
        if(token == IDL_TOKEN_ERROR)
        {
            return ERROR;
        }

        if(token == IDL_TOKEN_RIGHT_SQUARE_BRACKETS)
        {
            break;
        }
        else
        {
            hint->Puts(m_Lexer.GetCurVal());
        }
    }

    return OK;
}

status_t CIdlParser::ParseSentenceList(CIdlSentenceList *list)
{
    ASSERT(list);

    IdlLexerContext context;

    while(true)
    {            
        CIdlSentence sentence;
        sentence.Init();
 
        if(this->ParseSentence(&sentence))
        {
            list->Push(&sentence);
        }
        else
        {            
            m_Lexer.SaveContext(&context);
            int token = m_Lexer.Next();
            if(token != IDL_TOKEN_COMMA && token != IDL_TOKEN_COLON && token != IDL_TOKEN_EQUAL)
            {
                m_Lexer.RestoreContext(&context);
                break;
            }                
        }    
    }

    return OK;
}

status_t CIdlParser::ParseSentence(CIdlSentence *sentence)
{
    ASSERT(sentence);

    IdlLexerContext context;
    status_t parse_ok = ERROR;

    while(true)
    {
        m_Lexer.SaveContext(&context);
        int token = m_Lexer.Next();
        if(token == IDL_TOKEN_ERROR)
            break;
        CMem *value = m_Lexer.GetCurVal();
        ASSERT(value);
        
        if(token == IDL_TOKEN_WORD || token == IDL_TOKEN_NUMBER)
        {
            CIdlWord word;
            word.Init();
            word.SetName(value);
            sentence->Push(&word);
            parse_ok = OK;
        }
        else
        {
            m_Lexer.RestoreContext(&context);
            break;
        }     
    }

    return parse_ok;
}

status_t CIdlParser::ParseClass(CIdlClass *idl_class)
{
    ASSERT(idl_class);
    
    IdlLexerContext context;
    m_Lexer.SaveContext(&context);
    
    fsize_t start_pos = m_Lexer.GetCurPos();

    int token = m_Lexer.Next();

    if(token == IDL_TOKEN_WORD)
    {
        if(!m_Lexer.CurValueIs("class"))
        {
            UncertainError("'class' expected");
            m_Lexer.RestoreContext(&context);
            return ERROR;
        }
    }
    else
    {
        UncertainError("'class' expected");
        m_Lexer.RestoreContext(&context);
        return ERROR;
    }

    token = m_Lexer.Next();
    if(token != IDL_TOKEN_WORD)
    {
        m_Lexer.RestoreContext(&context);
        return ERROR;
    }

    CMem *value = m_Lexer.GetCurVal();
    idl_class->SetClassName(value);
    
    m_Lexer.SaveContext(&context);
    token = m_Lexer.Next();
    if(token == IDL_TOKEN_COLON)
    {
        CIdlSentenceList *bases = idl_class->GetBaseClasses();
        ASSERT(bases);      
        if(!this->ParseSentenceList(bases))
        {
            this->CertainError("fail parse base classes of %s",idl_class->GetClassNameStr());
            return ERROR;
        }
    }
    else
    {
        m_Lexer.RestoreContext(&context);
    }
    
    token = m_Lexer.Next();
    if(token != IDL_TOKEN_LEFT_BRACE)
    {
        this->CertainError("'{' expected, but got '%s'",m_Lexer.GetCurValStr());
        return ERROR;
    }
    
    if(!this->ParseClassBody(idl_class))
    {
        this->CertainError("parse class body fail,'%s'",m_Lexer.GetCurValStr());
        return ERROR;
    }

    token = m_Lexer.Next();
    if(token != IDL_TOKEN_RIGHT_BRACE)
    {
        this->CertainError("'}' expected, but got '%s'",m_Lexer.GetCurValStr());
        return ERROR;
    }

    fsize_t end_pos = m_Lexer.GetCurPos();

    CMem raw_source;
    raw_source.Init();
    m_Lexer.GetRawSource(start_pos,end_pos,&raw_source);
    idl_class->SetRawSource(&raw_source);

    return OK;
}

status_t CIdlParser::ParseVariableType(CIdlVariable *var)
{
    ASSERT(var);
    return this->ParseType(var->GetType());
}

status_t CIdlParser::ParseVariableName(CIdlVariable *var)
{
    ASSERT(var);

    IdlLexerContext context;
    m_Lexer.SaveContext(&context);
    
    int token = m_Lexer.Next();

    if(token == IDL_TOKEN_STAR)
    {
        var->GetType()->SetIsPointer(true);
        token = m_Lexer.Next();
    }

    if(token != IDL_TOKEN_WORD)
    {            
        UncertainError("parse variable name error: '%s'",m_Lexer.GetCurValStr());
        m_Lexer.RestoreContext(&context);
        return ERROR;
    }

    var->SetName(m_Lexer.GetCurValStr());

	m_Lexer.SaveContext(&context);
	token = m_Lexer.Next();
	if(token == IDL_TOKEN_LEFT_SQUARE_BRACKETS)
	{		
		LOCAL_MEM(array_size);
		while(!m_Lexer.IsEnd())
		{
		    int token1 = m_Lexer.NextTokenAll();
			if(token1 == IDL_TOKEN_WORD || token1 == IDL_TOKEN_STRING || token1 == IDL_TOKEN_NUMBER || token1 ==IDL_TOKEN_EMPTY)
			{
				array_size.Puts(m_Lexer.GetCurVal());
			}
			else if(token1 == IDL_TOKEN_RIGHT_SQUARE_BRACKETS)
			{
				var->GetType()->SetIsArray(true);
				array_size.Trim();
				var->GetType()->SetArraySize(&array_size);
				break;
			}
			else if(token1 != IDL_TOKEN_COMMENTS)
			{
				CertainError("error array size: '%s'",m_Lexer.GetCurValStr());
				m_Lexer.RestoreContext(&context);
				return ERROR;
			}
		}
	}
	else
	{
		m_Lexer.RestoreContext(&context);
	}

    m_Lexer.SaveContext(&context);
    token = m_Lexer.Next();
    if(token != IDL_TOKEN_EQUAL)
    {
        m_Lexer.RestoreContext(&context);
        return OK;
    }
    else
    {
        token = m_Lexer.Next();
        if(token == IDL_TOKEN_WORD || token == IDL_TOKEN_STRING || token == IDL_TOKEN_NUMBER)
        {
            var->SetInitValue(m_Lexer.GetCurVal());   
            var->SetHasInitValue(true);
            return OK;
        }
        else
        {
            this->CertainError("only string or number can be init value,'%s'",m_Lexer.GetCurValStr());
            return ERROR;
        }
    }
    return OK;
}

status_t CIdlParser::ParseType_ArrayTemplate(CIdlType *type)
{
    ASSERT(type);
    type->SetIsArray(true);
    int token = m_Lexer.Next();
    if(token != IDL_TOKEN_LESS_THAN)
    {
        CertainError("'<' expected, but got '%s'",m_Lexer.GetCurValStr());
        return ERROR;
    }

	LOCAL_MEM(ns);
	if(this->ParseNameSpace(&ns))
	{
		type->SetNameSpace(&ns);
	}

    token = m_Lexer.Next();
    if(token != IDL_TOKEN_WORD)
    {
        CertainError("not a valid array type '%s'",m_Lexer.GetCurValStr());
        return ERROR;
    }
    
    type->SetName(m_Lexer.GetCurVal());
    
    IdlLexerContext context;
    m_Lexer.SaveContext(&context);
    token = m_Lexer.Next();
    if(token == IDL_TOKEN_COMMA)
    {
        token = m_Lexer.Next();
        if(token == IDL_TOKEN_WORD || token == IDL_TOKEN_NUMBER)
        {
            type->SetArraySize(m_Lexer.GetCurVal());
        }
        else
        {
            CertainError("not a valid array len '%s'",m_Lexer.GetCurValStr());
            return ERROR;                
        }
    }
    else
    {
        m_Lexer.RestoreContext(&context);
    }
    
    token = m_Lexer.Next();
    if(token != IDL_TOKEN_GREATER_THAN)
    {
        CertainError("'>' expected, but got '%s'",m_Lexer.GetCurValStr());
        return ERROR;
    }   
    return OK;
}

status_t CIdlParser::ParseNameSpace(CMem *ns)
{
	ASSERT(ns);
	ns->SetSize(0);

    while(!m_Lexer.IsEnd())
    {
        IdlLexerContext context;
        m_Lexer.SaveContext(&context);
	    LOCAL_MEM(tmp);

	    int token = m_Lexer.Next();	
        if(token != IDL_TOKEN_WORD)
        {
            m_Lexer.RestoreContext(&context);
            break;
        }
	    tmp.Puts(m_Lexer.GetCurVal());
	    
	    token = m_Lexer.Next();
	    if(token != IDL_TOKEN_COLON)
	    {
            m_Lexer.RestoreContext(&context);
            break;
	    }

        token = m_Lexer.Next();
        if(token != IDL_TOKEN_COLON)
        {
            m_Lexer.RestoreContext(&context);
            break;
	    }

        if(ns->StrLen() > 0)ns->Puts("::");
        ns->Puts(&tmp);
    }

	return ns->StrLen() > 0;
}

status_t CIdlParser::ParseType(CIdlType *type)
{
    ASSERT(type);

	LOCAL_MEM(ns);
	
	if(this->ParseNameSpace(&ns))
	{
		type->SetNameSpace(&ns);
	}

    IdlLexerContext context;
    m_Lexer.SaveContext(&context);

    int token = m_Lexer.Next();
    if(token != IDL_TOKEN_WORD)
    {
        UncertainError("parse type fail");
        m_Lexer.RestoreContext(&context);
        return ERROR;
    }

    if(m_Lexer.CurValueIs("array"))
    {        
        if(!this->ParseType_ArrayTemplate(type))
        {
            CertainError("parse array template error.");
            return ERROR;
        }
    }
    else
    {
        type->SetName(m_Lexer.GetCurVal());
    }

    return OK;
}

status_t CIdlParser::ParseVariableNameList(CIdlVariableList *list)
{
    ASSERT(list);

    IdlLexerContext context_0;
    m_Lexer.SaveContext(&context_0);

    while(true)
    {
        CIdlVariable var_name;
        var_name.Init();
        if(!this->ParseVariableName(&var_name))
        {
            this->UncertainError("parse variable name fail");
            m_Lexer.RestoreContext(&context_0);
            return ERROR;
        }

        list->Push(&var_name);
        
        IdlLexerContext context;
        m_Lexer.SaveContext(&context);
        int token = m_Lexer.Next();

        if(token != IDL_TOKEN_COMMA)
        {
            m_Lexer.RestoreContext(&context);
            break;
        }
    }

    return OK;
}

status_t CIdlParser::ParseVariableList(CIdlVariableList *var_list)
{
    ASSERT(var_list);

    CIdlVariable var_type;
    var_type.Init();

    IdlLexerContext context;
    m_Lexer.SaveContext(&context);

    if(!this->ParseVariableType(&var_type))
    {
        this->UncertainError("parse variable type fail.");
        m_Lexer.RestoreContext(&context);
        return ERROR;
    }

    if(!this->ParseVariableNameList(var_list))
    {
        this->UncertainError("parse variable name list fail.");
        m_Lexer.RestoreContext(&context);
        return ERROR;
    }

    int token = m_Lexer.Next();
    if(token != IDL_TOKEN_SEMICOLON)
    {
        this->UncertainError("';' expected, but got '%s'",m_Lexer.GetCurValStr());
        m_Lexer.RestoreContext(&context);
        return ERROR;
    }
    
    //copy type and hints	
    for(int i = 0; i < var_list->GetLen(); i++)
    {
        CIdlVariable *var = var_list->GetElem(i);
        //pointer info is in var not in type
        //so save it before override type
        bool is_pointer = var->GetType()->IsPointer();
		bool is_array = var->GetType()->IsArray();
		LOCAL_MEM(arr_size);

		if(is_array)
		{
			arr_size.Puts(var->GetType()->GetArraySize());
		}

        var->SetType(var_type.GetType());
        var->GetType()->SetIsPointer(is_pointer);

		if(is_array)
		{
			var->GetType()->SetIsArray(is_array);
			var->GetType()->SetArraySize(&arr_size);
		}
    }

    return OK;
}

status_t CIdlParser::ParseClassBody(CIdlClass *idl_class)
{
    ASSERT(idl_class);

    CIdlHint *cur_hint = NULL;

    while(true)
    {
        if(cur_hint == NULL)
        {
            NEW(cur_hint,CIdlHint);
            cur_hint->Init();
        }
        
        int parsed = 0;

        LOCAL_MEM(tmp_hint);
        if(this->ParseHint(&tmp_hint))
        {
            parsed ++;
            cur_hint->AddHint(&tmp_hint);
        }

        CIdlVariableList var_list;
        var_list.Init();
        if(this->ParseVariableList(&var_list))
        {
            parsed ++;
            ASSERT(cur_hint);
            var_list.SetHint(cur_hint);
            idl_class->AddVariableList(&var_list);
            DEL(cur_hint);
        }

        CIdlFunction func;
        func.Init();
        if(this->ParseFunction(&func))
        {
            parsed ++;
            if(cur_hint)
            {
                func.SetHint(cur_hint);
                DEL(cur_hint);
            }
            idl_class->AddFunction(&func);
            
        }

        if(!parsed)
        {
            break;
        }
    }

    DEL(cur_hint);
    return !m_Lexer.HasError();
}

status_t CIdlParser::ParseFunction(CIdlFunction *func)
{
    ASSERT(func);

    CIdlTypeList ret_types;
    ret_types.Init();

    IdlLexerContext context;
    m_Lexer.SaveContext(&context);

    if(!this->ParseRetTypeList(&ret_types))
    {
        UncertainError("parse function return types fail");
        return ERROR;
    }

    func->SetRetTypeList(&ret_types);

    int token = m_Lexer.Next();
    if(token != IDL_TOKEN_WORD)
    {
        UncertainError("a word expected, but got '%s'",m_Lexer.GetCurValStr());
        m_Lexer.RestoreContext(&context);
        return ERROR;
    }

    func->SetName(m_Lexer.GetCurVal());
    token = m_Lexer.Next();
    
    if(token != IDL_TOKEN_LEFT_PARENTHESIS)
    {
        this->UncertainError("'(' expected, but got '%s'",m_Lexer.GetCurValStr());
        m_Lexer.RestoreContext(&context);
        return ERROR;
    }
    
    CIdlParamList param_list;
    param_list.Init();

    if(!this->ParseParamList(&param_list))
    {
        this->UncertainError("parse param list fail:%s",m_Lexer.GetCurValStr());
        m_Lexer.RestoreContext(&context);
        return ERROR;     
    }

    func->SetParamList(&param_list);

    token = m_Lexer.Next();    
    if(token != IDL_TOKEN_RIGHT_PARENTHESIS)
    {
        this->UncertainError("')' expected, but got '%s'",m_Lexer.GetCurValStr());
        m_Lexer.RestoreContext(&context);
        return ERROR;
    }

    token = m_Lexer.Next();
    if(token != IDL_TOKEN_SEMICOLON)
    {
        this->UncertainError("';' expected, but got '%s'",m_Lexer.GetCurValStr());
        m_Lexer.RestoreContext(&context);
        return ERROR;
    }

    CMem raw_source;
    raw_source.Init();
    m_Lexer.GetRawSource(context.cur_pos,m_Lexer.GetCurPos(),&raw_source);
    func->SetRawSource(&raw_source);
    return OK;
}

status_t CIdlParser::ParseRetTypeList(CIdlTypeList *type_list)
{
    ASSERT(type_list);
    
    IdlLexerContext context;
    status_t ret = ERROR;

	m_Lexer.SaveContext(&context);
	int token = m_Lexer.Next();

	//if return types start with '(' then
	//treat them as param list
	if(token == IDL_TOKEN_LEFT_PARENTHESIS)
	{		
		CIdlParamList param_list;
		param_list.Init();
		
		if(!this->ParseParamList(&param_list))
		{
			this->CertainError("parse ret types with name fail.");
			return ERROR;
		}

		token = m_Lexer.Next();
		if(token != IDL_TOKEN_RIGHT_PARENTHESIS)
		{
			this->CertainError("'(' expected, but got %s",m_Lexer.GetCurValStr());
			return ERROR;
		}

		for(int i = 0; i < param_list.GetLen(); i++)
		{
			CIdlParam *p = param_list.GetElem(i);
			ASSERT(p);

			CIdlType type;
			type.Copy(p->GetType());
			type.SetVarName(p->GetName());
			type.SetHasVarName(true);
			type_list->Push(&type);
		}

		return OK;
	}
	else
	{
		m_Lexer.RestoreContext(&context);
	}

    while(true)
    {        
        CIdlType type;
        type.Init();

        if(ParseType(&type))
        {
            m_Lexer.SaveContext(&context);
            if(m_Lexer.Next() == IDL_TOKEN_STAR)
            {
                type.SetIsPointer(true);
            }
            else
            {
                m_Lexer.RestoreContext(&context);
            }            
            type_list->Push(&type);
            ret = OK;
        }
        else
        {
            break;
        }
    
        m_Lexer.SaveContext(&context);
        int token = m_Lexer.Next();

        if(token != IDL_TOKEN_COMMA)
        {
            m_Lexer.RestoreContext(&context);
            break;
        }
    }

    return ret;
}

status_t CIdlParser::ClearUncertainError()
{
    return m_UncertainError.SetSize(0);
}

status_t CIdlParser::ParseParam(CIdlParam *param)
{
    ASSERT(param);

    IdlLexerContext context;
    m_Lexer.SaveContext(&context);

    LOCAL_MEM(tmp_hint);
    if(this->ParseHint(&tmp_hint))
    {
        param->AddHint(&tmp_hint);
    }
    
    bool has_type = false;

    CIdlType tmp_type;
    tmp_type.Init();
    if(this->ParseType(&tmp_type))
    {
        has_type = true;
        param->SetType(&tmp_type);
    }

    CIdlVariable tmp_var;
    tmp_var.Init();
    if(this->ParseVariableName(&tmp_var))
    {
        param->SetName(tmp_var.GetName());
        
        if(tmp_var.GetType()->IsPointer())
        {
            param->GetType()->SetIsPointer(true);
        }

        if(tmp_var.HasInitValue())
        {
            param->SetDefaultValue(tmp_var.GetInitValue());
            param->SetHasDefaultValue(true);
        }
    }
    else if(has_type)
    {
        //roll back, treat type as name
        param->SetName(tmp_type.GetName());
        param->ClearType();
    }
    else
    {
        //may be empty list
        m_Lexer.RestoreContext(&context);
        return ERROR;
    }

    return OK;
}

status_t CIdlParser::ParseParamList(CIdlParamList *param_list)
{
    ASSERT(param_list);
    
    IdlLexerContext context;    
    status_t ret = ERROR;
    
    while(true)
    {        
        CIdlParam param;
        param.Init();
        
        if(ParseParam(&param))
        {
            param_list->Push(&param);
            ret = OK;
        }
        else
        {
            ret = OK; //maybe empty list
            break;
        }
        
        m_Lexer.SaveContext(&context);
        int token = m_Lexer.Next();
        
        if(token != IDL_TOKEN_COMMA)
        {
            m_Lexer.RestoreContext(&context);
            break;
        }
    }

    return ret;
}

bool CIdlParser::HasErrors()
{
    return m_CertainError.StrLen() > 0;
}

CMemFile * CIdlParser::GetCertainErrors()
{
    return &m_CertainError;
}

CMemFile * CIdlParser::GetUncertainErrors()
{
    return &m_UncertainError;
}

status_t CIdlParser::ReportErrors()
{
    if(this->HasErrors())
    {
        m_CertainError.Dump();
        m_UncertainError.Dump();
    }
    return OK;
}
