#pragma once
#include <afxsock.h>

class CMySocket : public CAsyncSocket
{
public:
    HWND m_hNotifyWnd = NULL;
    void SetNotifyWnd(HWND hWnd) { m_hNotifyWnd = hWnd; }
protected:
    virtual void OnReceive(int nErrorCode);
};
