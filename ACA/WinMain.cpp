#include "Main.h"
#include <tchar.h>
#include <stdexcept>
#include <Windows.h>

int _stdcall WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
    //���C���̃V�[�����쐬���A���s
    try
    {
        std::unique_ptr<aca::scene::Main> m(new aca::scene::Main());
        m->execute();
    }
	//�{���͂���ȗ�O�������Ă͂����Ȃ��c
    catch(std::runtime_error& e)
    {
        MessageBox(nullptr, _T(e.what()), _T("runtime error"), MB_OK | MB_ICONEXCLAMATION);
    }
    catch(std::out_of_range& e)
    {
        MessageBox(nullptr, _T(e.what()), _T("out of range error"), MB_OK | MB_ICONEXCLAMATION);
    }
    catch(std::invalid_argument& e)
    {
        MessageBox(nullptr, _T(e.what()), _T("invalidargument error"), MB_OK | MB_ICONEXCLAMATION);
    }
    catch(std::logic_error& e)
    {
        MessageBox(nullptr, _T(e.what()), _T("logic error"), MB_OK | MB_ICONEXCLAMATION);
    }

    return 0;
}