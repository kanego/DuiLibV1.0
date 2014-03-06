#ifndef __UIRENDER_H__
#define __UIRENDER_H__

#pragma once

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

//��Ⱦ�ü�����Ҫ����������Ⱦ����Ĵ�С��������dc�ϻ��Ƶ����򣬷�ֹ�ӿռ���Ƶ����ؼ���ࣨFloat ���Կؼ����⣩
class UILIB_API CRenderClip
{
public:
    ~CRenderClip();
    RECT rcItem;
    HDC hDC;
    HRGN hRgn;
    HRGN hOldRgn;

	//����һ����������, hDC���ھ��, rc����, clip[out]������
    static void GenerateClip(HDC hDC, RECT rc, CRenderClip& clip);

	//����һ��Բ�Ǽ�������, hDC���ھ��, rc����, width ����Բ�ǻ���, height����Բ�ǻ���, clip[out]������
    static void GenerateRoundClip(HDC hDC, RECT rc, RECT rcItem, int width, int height, CRenderClip& clip);
	
	//ʹ��������Ծ������Ϊ������, hDC���ھ��, clip������
    static void UseOldClipBegin(HDC hDC, CRenderClip& clip);
	
	// ʹ�õ�ǰ�ؼ���Ч������Ϊ������, hDC���ھ��, clip������
    static void UseOldClipEnd(HDC hDC, CRenderClip& clip);
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CRenderEngine
{
public:
    static DWORD AdjustColor(DWORD dwColor, short H, short S, short L);
	
	//mask:����ɫ
    static TImageInfo* LoadImage(STRINGorID bitmap, LPCTSTR type = NULL, DWORD mask = 0);
    static void FreeImage(const TImageInfo* bitmap);

	///*���� ����ͼ��
	//	hDC �豸���
	//	hBitmap λͼ���
	//	rc ��������
	//	rcPaint ��������
	//	rcBmpPart λͼ����
	//	rcConrners ��������
	//	alphaChannel alphaͨ��
	//	uFade ͸����
	//	hole ����
	//  xtiled ����ƽ��
	//	ytiled ����ƽ��
    static void DrawImage(HDC hDC, HBITMAP hBitmap, const RECT& rc, const RECT& rcPaint, \
        const RECT& rcBmpPart, const RECT& rcCorners, bool alphaChannel, BYTE uFade = 255, 
        bool hole = false, bool xtiled = false, bool ytiled = false);

    static bool DrawImageString(HDC hDC, CPaintManagerUI* pManager, const RECT& rcItem, const RECT& rcPaint, 
        LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);
    static void DrawColor(HDC hDC, const RECT& rc, DWORD color);

	//���ƽ��䣬dwfirst ��ɫ1 ��dwsecond Ϊ��ɫ2 ��bVertical Ϊtrue ��ֱ���䣬Ϊfalseʱ ���򽥱�
    static void DrawGradient(HDC hDC, const RECT& rc, DWORD dwFirst, DWORD dwSecond, bool bVertical, int nSteps);

    // ���º����е���ɫ����alphaֵ��Ч
    static void DrawLine(HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor,int nStyle = PS_SOLID);
    static void DrawRect(HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor);
    static void DrawRoundRect(HDC hDC, const RECT& rc, int width, int height, int nSize, DWORD dwPenColor);
    static void DrawText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, \
        DWORD dwTextColor, int iFont, UINT uStyle);
    static void DrawHtmlText(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, 
        DWORD dwTextColor, RECT* pLinks, CDuiString* sLinks, int& nLinkRects, UINT uStyle);
    static HBITMAP GenerateBitmap(CPaintManagerUI* pManager, CControlUI* pControl, RECT rc);
	static SIZE GetTextSize(HDC hDC, CPaintManagerUI* pManager , LPCTSTR pstrText, int iFont, UINT uStyle);
};

} // namespace DuiLib

#endif // __UIRENDER_H__
