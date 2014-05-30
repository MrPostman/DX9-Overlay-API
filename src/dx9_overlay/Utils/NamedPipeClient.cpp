#include "Windows.h"
#include "NamedPipeClient.h"
#include "Bitstream.h"

#include <iostream>

CNamedPipeClient::CNamedPipeClient(const char *Pipe, CBitStream *bsIn, CBitStream *bsOut) :
m_bSuccess(false)
{
	char szData[BUFSIZE] = { 0 };
	char szPipe[MAX_PATH + 1] = { 0 };
	DWORD dwReaded;

	sprintf(szPipe, "\\\\.\\pipe\\%s", Pipe);

	if (CallNamedPipe(szPipe, (LPVOID)bsIn->GetData(), bsIn->GetNumberOfBytesUsed(), szData, sizeof(szData), &dwReaded, TIME_OUT))
	{
		bsOut->SetData(szData, sizeof(szData));
		m_bSuccess = true;
	}
}

bool CNamedPipeClient::Success() const
{
	return m_bSuccess;
}