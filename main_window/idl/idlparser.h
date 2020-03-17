#ifndef __S2_IDLPARSER_H
#define __S2_IDLPARSER_H

#include "cruntime.h"
#include "mem.h"
#include "memfile.h"
#include "idllexer.h"
#include "idlmodule.h"
#include "idlvariablelist.h"
#include "idltypelist.h"
#include "idlfunctionlist.h"

class CIdlParser{
public:
    WEAK_REF_DEFINE();
public:
	CIdlLexer m_Lexer;
    CMemFile m_UncertainError;
    CMemFile m_CertainError;
public:
	status_t ReportErrors();
	CMemFile * GetUncertainErrors();
	CMemFile * GetCertainErrors();
	bool HasErrors();
	status_t ParseParamList(CIdlParamList *param_list);
	status_t ParseParam(CIdlParam *param);
	status_t ClearUncertainError();
    status_t CertainError(const char* format, ...);
    status_t UncertainError(const char* format, ...);
	status_t ParseRetTypeList(CIdlTypeList *type_list);
	status_t ParseFunction(CIdlFunction *func);
	status_t ParseClassBody(CIdlClass *idl_class);
	status_t ParseVariableList(CIdlVariableList *var_list);
	status_t ParseVariableNameList(CIdlVariableList *list);
    status_t ParseVariableName(CIdlVariable *var);
    status_t ParseType(CIdlType *type);
    status_t ParseType_ArrayTemplate(CIdlType *type);
	status_t ParseVariableType(CIdlVariable *var);
	status_t ParseClass(CIdlClass *idl_class);
	status_t ParseSentence(CIdlSentence *sentence);
	status_t ParseSentenceList(CIdlSentenceList *list);
    status_t ParseHint(CMem *hint);    
	status_t ParseAll(CIdlModule *idl_module);
	status_t LoadSource(const char *idlfile);
    status_t LoadSource(CFileBase *file);
	CIdlParser();
	virtual ~CIdlParser();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
	status_t Copy(CIdlParser *_p);
	int Comp(CIdlParser *_p);
	status_t Print(CFileBase *_buf);
	CIdlLexer* GetLexer();
	status_t SetLexer(CIdlLexer* _lexer);
	status_t ParseNameSpace(CMem *ns);
};

#endif
