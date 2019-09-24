#ifndef __GIF_ENCODER_H
#define __GIF_ENCODER_H

#include "mem.h"
#include "memfile.h"
#include "file.h"
#include "ximage.h"

class CGifEncoder{
public:
    WEAK_REF_ID_DEFINE();
public:
    int m_Loops;
    bool m_LocalDispMeth;
    bool m_LocalColorMap;
    bool m_IsFirstFrame;
    CFileBase *m_File;
    CFile m_TmpFile;
    char m_comment[256];
    BYTE m_disposal_method;
public:
	status_t AddFrame(CxImage *img);
	status_t End();
	status_t Begin(const char *filename);
	status_t Begin(CFileBase *file);
    CGifEncoder();
    virtual ~CGifEncoder();

    status_t InitBasic();
    status_t Init();
    status_t Destroy();

    int GetLoops();
    bool GetLocalDispMeth();
    bool GetLocalColorMap();
    bool GetIsFirstFrame();
    CFileBase* GetFile();
    CFile* GetTmpFile();
    status_t SetLoops(int _loops);
    status_t SetLocalDispMeth(bool _localdispmeth);
    status_t SetLocalColorMap(bool _localcolormap);
    status_t SetIsFirstFrame(bool _isfirstframe);
    status_t SetFile(CFileBase *_file);

    status_t SetComment(const char *comment);
    status_t SetDisposalMethod(BYTE dm);
    void EncodeComment();
};

#endif
