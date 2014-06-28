/*
* This file is part of dslibbluray
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library. If not, see
* <http://www.gnu.org/licenses/>.
*/

#ifndef _IBDNAV_H_
#define _IBDNAV_H_

typedef enum
{
	BD_KEY_None = 0xffff,

	/* numeric key events */
	BD_KEY_0 = 0,
	BD_KEY_1 = 1,
	BD_KEY_2 = 2,
	BD_KEY_3 = 3,
	BD_KEY_4 = 4,
	BD_KEY_5 = 5,
	BD_KEY_6 = 6,
	BD_KEY_7 = 7,
	BD_KEY_8 = 8,
	BD_KEY_9 = 9,

	/* */
	BD_KEY_Root_Menu = 10,  /* open root menu */
	BD_KEY_Popup = 11,  /* toggle popup menu */

	/* interactive key events */
	BD_KEY_Up = 12,
	BD_KEY_Down = 13,
	BD_KEY_Left = 14,
	BD_KEY_Right = 15,
	BD_KEY_Enter = 16,

	BD_VK_Red = 403,
	BD_VK_Green = 404,
	BD_VL_Yellow = 405,
	BD_VK_Blue = 406,

	/* Mouse click */
	/* Translated to BD_VK_ENTER if mouse is over valid button */
	BD_KEY_Mouse_Activate = 17,

} BDKeyCode;

typedef enum
{
	BD_DOMAIN_First_Play,
	BD_DOMAIN_Popup_Menu,
	BD_DOMAIN_Event_Menu,
	BD_DOMAIN_Title,
	BD_DOMAIN_Stop
} BDDomain;

typedef enum
{
	BD_EVENT_None = 0x200,
	BD_EVENT_Error,       /* Fatal error. Playback can't be continued. */ /* 0x201 */
	BD_EVENT_Read_Error,  /* Reading of .m2ts aligned unit failed. Next call to read will try next block. */ /* 0x202 */
	BD_EVENT_Encrypted,   /* .m2ts file is encrypted and can't be played */ /* 0x203 */

	/* current playback position */
	BD_EVENT_Angle,     /* current angle, 1...N */ /* 0x204 */
	BD_EVENT_Title,     /* current title, 1...N (0 = top menu) */ /* 0x205 */
	BD_EVENT_Playlist,  /* current playlist (xxxxx.mpls) */ /* 0x206 */
	BD_EVENT_Playitem,  /* current play item, 0...N-1  */ /* 0x207 */
	BD_EVENT_Chapter,   /* current chapter, 1...N */ /* 0x208 */
	BD_EVENT_End_Of_Title, /* 0x209 */

	/* stream selection */
	BD_EVENT_Audio_Stream,           /* 1..32,  0xff  = none */ /* 0x20a */
	BD_EVENT_IG_Stream,              /* 1..32                */ /* 0x20b */
	BD_EVENT_PG_Textst_Stream,       /* 1..255, 0xfff = none */ /* 0x20c */
	BD_EVENT_PIP_PG_Textst_Stream,   /* 1..255, 0xfff = none */ /* 0x20d */
	BD_EVENT_Secondary_Audio_Stream, /* 1..32,  0xff  = none */ /* 0x20e */
	BD_EVENT_Secondary_Video_Stream, /* 1..32,  0xff  = none */ /* 0x20f */

	BD_EVENT_PG_Textst,              /* 0 - disable, 1 - enable */ /* 0x210 */
	BD_EVENT_PIP_PG_Textst,          /* 0 - disable, 1 - enable */ /* 0x211 */
	BD_EVENT_Secondary_Audio,        /* 0 - disable, 1 - enable */ /* 0x212 */
	BD_EVENT_Secondary_Video,        /* 0 - disable, 1 - enable */ /* 0x213 */
	BD_EVENT_Secondary_Video_Size,   /* 0 - PIP, 0xf - fullscreen */ /* 0x214 */

	/* HDMV VM or JVM seeked the stream. Next read() will return data from new position. */
	BD_EVENT_Seek, /* 0x215 */

	/* still playback (pause) */
	BD_EVENT_Still,                  /* 0 - off, 1 - on */ /* 0x215 */

	/* Still playback for n seconds (reached end of still mode play item) */
	BD_EVENT_Still_Time,             /* 0 = infinite ; 1...300 = seconds */ /* 0x216 */

	/* Play sound effect */
	BD_EVENT_Sound_Effect,           /* effect ID */ /* 0x217 */

	/* Pop-Up menu available */
	BD_EVENT_Popup,                  /* 0 - no, 1 - yes */ /* 0x218 */

	/* Interactive menu visible */
	BD_EVENT_Menu,                   /* 0 - no, 1 - yes */ /* 0x219 */

	/* 3D */
	BD_EVENT_Stereoscopic_Status	 /* 0 - 2D, 1 - 3D */ /* 0x21a */
} BDEvent;

typedef struct {
	ULONG				TitleNum;
	ULONG				ChapterNum;
	REFERENCE_TIME	TimeCode;
} BDPlaybackLocation;


#if defined(__cplusplus) && !defined(CINTERFACE)

MIDL_INTERFACE("3F38E88C-1191-4402-BB62-22657B2BC636")
IBDNav : public IUnknown
{
public:

	virtual HRESULT STDMETHODCALLTYPE KeyInput(
		/* [in] */ ULONG ulKeyCode) = 0;

	virtual HRESULT STDMETHODCALLTYPE SelectAtPosition(
		/* [in] */ POINT point,
		/* [in] */ RECT windowRect) = 0;

	virtual HRESULT STDMETHODCALLTYPE ActivateAtPosition(
		/* [in] */ POINT point,
		/* [in] */ RECT windowRect) = 0;

	virtual HRESULT STDMETHODCALLTYPE PlayNextChapter() = 0;

	virtual HRESULT STDMETHODCALLTYPE PlayPrevChapter() = 0;

	virtual HRESULT STDMETHODCALLTYPE PlayChapter(
		/* [in] */ ULONG ulChapter) = 0;

	virtual HRESULT STDMETHODCALLTYPE ReplayChapter() = 0;

	virtual HRESULT STDMETHODCALLTYPE PlayChapterInTitle(
		/* [in] */ ULONG ulTitle,
		/* [in] */ ULONG ulChapter) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNumberOfChapters(
		/* [in] */ ULONG ulTitle,
		/* [out] */ ULONG *pulNumOfChapters) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNumberOfTitles(
		/* [out] */ ULONG *pulNumOfTitles) = 0;

	virtual HRESULT STDMETHODCALLTYPE ShowMenu() = 0;

	virtual HRESULT STDMETHODCALLTYPE SelectAngle(
		/* [in] */ ULONG ulAngle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentAngle(
		/* [out] */ ULONG *pulAnglesAvailable,
		/* [out] */ ULONG *pulCurrentAngle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTotalTitleTime(
		/* [out] */ REFERENCE_TIME *pTotalTime) = 0;

	virtual HRESULT STDMETHODCALLTYPE PlayAtTime(
		/* [in] */ REFERENCE_TIME *pTime) = 0;

	virtual HRESULT STDMETHODCALLTYPE PlayAtTimeInTitle(
		/* [in] */ ULONG uiTitle,
		/* [in] */ REFERENCE_TIME *pTime) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentAudio(
		/* [out] */ ULONG *pulStreamsAvailable,
		/* [out] */ ULONG *pulCurrentStream) = 0;

	virtual HRESULT STDMETHODCALLTYPE SelectAudioStream(
		/* [in] */ ULONG ulAudio) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAudioLanguage(
		/* [in] */ ULONG ulStream,
		/* [out] */ LCID *pLanguage) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetSubpictureState(
		/* [in] */ BOOL bState) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentSubpicture(
		/* [out] */ ULONG *pulStreamsAvailable,
		/* [out] */ ULONG *pulCurrentStream,
		/* [out] */ BOOL *pbIsDisabled) = 0;

	virtual HRESULT STDMETHODCALLTYPE SelectSubpictureStream(
		/* [in] */ ULONG ulSubPicture) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetSubpictureLanguage(
		/* [in] */ ULONG ulStream,
		/* [out] */ LCID *pLanguage) = 0;

	virtual HRESULT STDMETHODCALLTYPE SelectDefaultAudioLanguage(
		/* [in] */ LCID Language) = 0;

	virtual HRESULT STDMETHODCALLTYPE SelectDefaultMenuLanguage(
		/* [in] */ LCID Language) = 0;

	virtual HRESULT STDMETHODCALLTYPE SelectDefaultSubpictureLanguage(
		/* [in] */ LCID Language) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDefaultAudioLanguage(
		/* [out] */ LCID *pLanguage) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDefaultMenuLanguage(
		/* [out] */ LCID *pLanguage) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDefaultSubpictureLanguage(
		/* [out] */ LCID *pLanguage) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentDomain(
		/* [out] */ BDDomain *pDomain) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentLocation(
		/* [out] */ BDPlaybackLocation *pLocation) = 0;

	virtual HRESULT STDMETHODCALLTYPE SelectParentalCountry(
		/* [in] */ BYTE bCountry[2]) = 0;

	virtual HRESULT STDMETHODCALLTYPE SelectParentalLevel(
		/* [in] */ BYTE bParentalLevel) = 0;

};

#else 	/* C style interface */

typedef struct IBDNavVtbl
{
	BEGIN_INTERFACE

		HRESULT(STDMETHODCALLTYPE *KeyInput)(
		IBDNav * This,
		/* [in] */ ULONG ulKeyCode);

		HRESULT(STDMETHODCALLTYPE *SelectAtPosition)(
			IBDNav * This,
			/* [in] */ POINT point,
			/* [in] */ RECT windowRect);

		HRESULT(STDMETHODCALLTYPE *ActivateAtPosition)(
			IBDNav * This,
			/* [in] */ POINT point,
			/* [in] */ RECT windowRect);

		HRESULT(STDMETHODCALLTYPE *PlayNextChapter)(
			IBDNav * This);

		HRESULT(STDMETHODCALLTYPE *PlayPrevChapter)(
			IBDNav * This);

		HRESULT(STDMETHODCALLTYPE *ReplayChapter)(
			IBDNav * This);

		HRESULT(STDMETHODCALLTYPE *PlayChapter)(
			IBDNav * This,
			/* [in] */ ULONG ulChapter);

		HRESULT(STDMETHODCALLTYPE *PlayChapterInTitle)(
			IBDNav * This,
			/* [in] */ ULONG ulTitle,
			/* [in] */ ULONG ulChapter;

		HRESULT(STDMETHODCALLTYPE *GetNumberOfChapters)(
			IBDNav * This,
			/* [in] */ ULONG ulTitle,
			/* [out] */ ULONG *pulNumOfChapters);

		HRESULT(STDMETHODCALLTYPE *GetNumberOfTitles)(
			IBDNav * This,
			/* [out] */ ULONG *pulNumOfTitles);

		HRESULT(STDMETHODCALLTYPE *ShowMenu)(
			IBDNav * This);

		HRESULT(STDMETHODCALLTYPE *SelectAngle)(
			IBDNav * This,
			/* [in] */ ULONG ulAngle);

		HRESULT(STDMETHODCALLTYPE *GetCurrentAngle)(
			IBDNav * This,
			/* [out] */ ULONG *pulAnglesAvailable,
			/* [out] */ ULONG *pulCurrentAngle);

		HRESULT(STDMETHODCALLTYPE *GetTotalTitleTime)(
			IBDNav * This,
			/* [out] */ REFERENCE_TIME *pTotalTime);

		HRESULT(STDMETHODCALLTYPE *PlayAtTime)(
			IBDNav * This,
			/* [in] */ REFERENCE_TIME *pTime);

		HRESULT(STDMETHODCALLTYPE *PlayAtTimeInTitle)(
			IBDNav * This,
			/* [in] */ ULONG uiTitle,
			/* [in] */ REFERENCE_TIME *pTime);

		HRESULT(STDMETHODCALLTYPE *GetCurrentAudio)(
			IBDNav * This,
			/* [out] */ ULONG *pulStreamsAvailable,
			/* [out] */ ULONG *pulCurrentStream);

		HRESULT(STDMETHODCALLTYPE *SelectAudioStream)(
			IBDNav * This,
			/* [in] */ ULONG ulAudio);

		HRESULT(STDMETHODCALLTYPE *GetAudioLanguage)(
			IBDNav * This,
			/* [in] */ ULONG ulStream,
			/* [out] */ LCID *pLanguage);

		HRESULT(STDMETHODCALLTYPE *SetSubpictureState)(
			IBDNav * This,
			/* [in] */ BOOL bState);

		HRESULT(STDMETHODCALLTYPE *GetCurrentSubpicture)(
			IBDNav * This,
			/* [out] */ ULONG *pulStreamsAvailable,
			/* [out] */ ULONG *pulCurrentStream,
			/* [out] */ BOOL *pbIsDisabled);

		HRESULT(STDMETHODCALLTYPE *SelectSubpictureStream)(
			IBDNav * This,
			/* [in] */ ULONG ulSubPicture);

		HRESULT(STDMETHODCALLTYPE *GetSubpictureLanguage)(
			IBDNav * This,
			/* [in] */ ULONG ulStream,
			/* [out] */ LCID *pLanguage);

		HRESULT(STDMETHODCALLTYPE *SelectDefaultAudioLanguage)(
			IBDNav * This,
			/* [in] */ LCID Language);

		HRESULT(STDMETHODCALLTYPE *SelectDefaultMenuLanguage)(
			IBDNav * This,
			/* [in] */ LCID Language);

		HRESULT(STDMETHODCALLTYPE *SelectDefaultSubpictureLanguage)(
			IBDNav * This,
			/* [in] */ LCID Language);

		HRESULT(STDMETHODCALLTYPE *GetDefaultAudioLanguage)(
			IBDNav * This,
			/* [out] */ LCID pLanguage);

		HRESULT(STDMETHODCALLTYPE *GetDefaultMenuLanguage)(
			IBDNav * This,
			/* [out] */ LCID pLanguage);

		HRESULT(STDMETHODCALLTYPE *GetDefaultSubpictureLanguage)(
			IBDNav * This,
			/* [out] */ LCID pLanguage);

		HRESULT(STDMETHODCALLTYPE *GetCurrentDomain)(
			IBDNav * This,
			/* [out] */ BDDomain *pDomain);

		HRESULT(STDMETHODCALLTYPE *GetCurrentLocation)(
			IBDNav * This,
			/* [out] */ BDPlaybackLocation *pLocation);

		HRESULT(STDMETHODCALLTYPE *SelectParentalCountry)(
			IBDNav * This,
			/* [in] */ BYTE bCountry[2]);

		HRESULT(STDMETHODCALLTYPE *SelectParentalLevel)(
			IBDNav * This,
			/* [in] */ BYTE bParentalLevel);

	END_INTERFACE
} IBDNavVtbl;

interface IBDNav
{
	CONST_VTBL struct IBDNavVtbl *lpVtbl;
};

#endif

#endif // _IBDNAV_H_

