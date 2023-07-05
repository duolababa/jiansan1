#include "../pch.h"
#include "ClipboardExample.h"

/*
==============================================================================================

开源声明： 
，本着一起提高网络安全水平研究了一下UE4游戏的安全，把现有的研究成果和大家分享一下。本人申明，本套源码仅用于开源学习，禁止将本套源码用作任何商业用途和非法用途，如果你使用本套源码，代表已经同意了此声明，所造成的任何后果和损失，由使用者自行承担。

技术交流QQ群782282356
==============================================================================================

*/
ClipboardExample::ClipboardExample()
 {
     errCode=0;
     hClip=NULL;
 }
 
 ClipboardExample::~ClipboardExample()
 {
     if(hClip)
         CloseHandle(hClip);
 }
 
 BOOL ClipboardExample::SetClipData(char *pstr)
 {
     if(OpenClipboard(NULL))
     {
         char *pBuf;
         if(0==EmptyClipboard())
         {
             CloseClipboard();
             return false;
         }
         hClip=GlobalAlloc(GMEM_MOVEABLE,strlen(pstr)+1);
         if(NULL==hClip)
         {
             CloseClipboard();
             return false;
         }
         pBuf=(char*)GlobalLock(hClip);
         if(NULL==pBuf)
         {
             CloseClipboard();
             return false;
         }
         strcpy(pBuf,pstr);
         GlobalUnlock(hClip);
         
         if(NULL==SetClipboardData(CF_TEXT,hClip))
         {
             CloseClipboard();
             return false;
         }
 
         CloseClipboard();
     }
     return true;
 }
/*
==============================================================================================

开源声明： 
，本着一起提高网络安全水平研究了一下UE4游戏的安全，把现有的研究成果和大家分享一下。本人申明，本套源码仅用于开源学习，禁止将本套源码用作任何商业用途和非法用途，如果你使用本套源码，代表已经同意了此声明，所造成的任何后果和损失，由使用者自行承担。

技术交流QQ群782282356
==============================================================================================

*/
 
 char* ClipboardExample::GetClipData()
 {
     char* pstr=0;
     if(OpenClipboard(NULL))
     {
         if(IsClipboardFormatAvailable(CF_TEXT))
         {
             hClip = GetClipboardData(CF_TEXT);
             if(NULL==hClip)
             {
                 CloseClipboard();
                 return NULL;
             }
             pstr = (char*)GlobalLock(hClip);
             GlobalUnlock(hClip);
             CloseClipboard();
         }
     }
     return pstr;
 }

 /*
==============================================================================================

开源声明： 
，本着一起提高网络安全水平研究了一下UE4游戏的安全，把现有的研究成果和大家分享一下。本人申明，本套源码仅用于开源学习，禁止将本套源码用作任何商业用途和非法用途，如果你使用本套源码，代表已经同意了此声明，所造成的任何后果和损失，由使用者自行承担。

技术交流QQ群782282356
==============================================================================================

*/
 /*char* ClipboardExample::GetError()
 {
     errCode = GetLastError();
     char pstr[128];
     itoa(errCode,pstr,10);
     return pstr;
 }*/