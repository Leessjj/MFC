#include "pch.h"
#include "MySocket.h"

void CMySocket::OnReceive(int nErrorCode)
{
    AfxMessageBox(_T("OnReceive ȣ���!"));  // �� �߰�
    char buf[256] = { 0 };
    int nRecv = Receive(buf, 255);
    if (nRecv > 0 && m_hNotifyWnd)
    {
        ::SendMessage(m_hNotifyWnd, WM_APP + 1, 0, (LPARAM)new CString(buf));
    }
    CAsyncSocket::OnReceive(nErrorCode);
}