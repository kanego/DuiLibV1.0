#ifndef __UIRENDER_H__
#define __UIRENDER_H__

#pragma once

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

//渲染裁剪，主要用来控制渲染区域的大小，设置在dc上绘制的区域，防止子空间绘制到父控件外侧（Float 属性控件除外）
class UILIB_API CRenderClip
{
public:
    ~CRenderClip();
    RECT rcItem;
    HDC hDC;
    HRGN hRgn;
    HRGN hOldRgn;

	//产生一个剪切区域, hDC窗口句柄, rc区域, clip[out]剪切区
    static void GenerateClip(HDC hDC, RECT rc, CRenderClip& clip);

	//产生一个圆角剪切区域, hDC窗口句柄, rc区域, width 横向圆角弧度, height纵向圆角弧度, clip[out]剪切区
    static void GenerateRoundClip(HDC hDC, RECT rc, RECT rcItem, int width, int height, CRenderClip& clip);
	
	//使用整个活跃区域作为剪切区, hDC窗口句柄, clip剪切区
    static void UseOldClipBegin(HDC hDC, CRenderClip& clip);
	
	// 使用当前控件有效区域作为剪切区, hDC窗口句柄, clip剪切区
    static void UseOldClipEnd(HDC hDC, CRenderClip& clip);
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CRenderEngine
{
public:
    static DWORD AdjustColor(DWORD dwColor, short H, short S, short L);
	
	//mask:隐蔽色
    static TImageInfo* LoadImage(STRINGorID bitmap, LPCTSTR type = NULL, DWORD mask = 0);
    static void FreeImage(const TImageInfo* bitmap);

	///*功能 绘制图像
	//	hDC 设备句柄
	//	hBitmap 位图句柄
	//	rc 对象区域
	//	rcPaint 绘制区域
	//	rcBmpPart 位图区域
	//	rcConrners 拉伸区域
	//	alphaChannel alpha通道
	//	uFade 透明度
	//	hole 居中
	//  xtiled 横向平铺
	//	ytiled 纵向平铺
    static void DrawImage(HDC hDC, HBITMAP hBitmap, const RECT& rc, const RECT& rcPaint, \
        const RECT& rcBmpPart, const RECT& rcCorners, bool alphaChannel, BYTE uFade = 255, 
        bool hole = false, bool xtiled = false, bool ytiled = false);

    static bool DrawImageString(HDC hDC, CPaintManagerUI* pManager, const RECT& rcItem, const RECT& rcPaint, 
        LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);
    static void DrawColor(HDC hDC, const RECT& rc, DWORD color);

	//绘制渐变，dwfirst 颜色1 ，dwsecond 为颜色2 ，bVertical 为true 垂直渐变，为false时 横向渐变
    static void DrawGradient(HDC hDC, const RECT& rc, DWORD dwFirst, DWORD dwSecond, bool bVertical, int nSteps);

    // 以下函数中的颜色参数alpha值无效
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
