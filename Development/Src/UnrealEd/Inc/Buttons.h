/*=============================================================================
	Buttons.h: Special controls based on standard buttons

	Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

/*-----------------------------------------------------------------------------
	WxBitmapButton.

	A wrapper for wxBitmapButton.
-----------------------------------------------------------------------------*/

class WxBitmapButton : public wxBitmapButton
{
	DECLARE_DYNAMIC_CLASS(WxBitmapButton);
public:
	WxBitmapButton();
	WxBitmapButton( wxWindow* InParent, wxWindowID InID, WxBitmap InBitmap, const wxPoint& InPos = wxDefaultPosition, const wxSize& InSize = wxDefaultSize );
	~WxBitmapButton();

	void OnRightButtonDown( wxMouseEvent& In );
	void WxBitmapButton::OnRightButtonUp(wxMouseEvent& In);
	void OnRightClick(wxCommandEvent& In);

	// Declare an empty erase background callback to prevent flicker.
	void OnEraseBackground(wxEraseEvent& event) {};

	DECLARE_EVENT_TABLE()
};

/*-----------------------------------------------------------------------------
	WxMenuButton.

	Displays a menu below the button when clicked.
-----------------------------------------------------------------------------*/

class WxMenuButton : public WxBitmapButton
{
public:
	WxMenuButton();
	WxMenuButton( wxWindow* InParent, wxWindowID InID, WxBitmap* InBitmap, wxMenu* InMenu, const wxPoint& InPos = wxDefaultPosition, const wxSize& InSize = wxDefaultSize );
	~WxMenuButton();

	void Create( wxWindow* InParent, wxWindowID InID, WxBitmap* InBitmap, wxMenu* InMenu, const wxPoint& InPos, const wxSize& InSize );

	wxMenu* Menu;			// The menu to display when clicked

	void OnClick( wxCommandEvent &In );

	DECLARE_EVENT_TABLE()
};

/*-----------------------------------------------------------------------------
	WxBitmapStateButton.
-----------------------------------------------------------------------------*/

class FBitmapStateButtonState
{
public:
	FBitmapStateButtonState();
	FBitmapStateButtonState( INT InID, wxBitmap* InBitmap );
	~FBitmapStateButtonState();

	INT ID;
	wxBitmap* Bitmap;
};

/** A button that can switch between multiple states */
class WxBitmapStateButton : public WxBitmapButton
{
public:

	/** Construct a WxBitmapStateButton */
	WxBitmapStateButton();

	/** 
	 * Construct a WxBitmapStateButton
	 *
	 * @param	InParent				Parent window of this button
	 * @param	InMsgTarget				Unused?
	 * @param	InID					ID of this button
	 * @param	InPos					Position of this button
	 * @param	InSize					Size of this button
	 * @param	bCycleOnLeftMouseDown	If TRUE, left mouse down on the button will cycle to the next bitmap state
	 */
	WxBitmapStateButton( wxWindow* InParent, wxWindow* InMsgTarget, wxWindowID InID, const wxPoint& InPos=wxDefaultPosition, const wxSize& InSize=wxDefaultSize, UBOOL bCycleOnLeftMouseDown=TRUE );
	
	/** Destruct a WxBitmapStateButton */
	~WxBitmapStateButton();

	/**
	 * Add a new state to the button
	 *
	 * @param	InID		ID of the new state
	 * @param	InBitmap	Bitmap to use for the new state
	 */
	void AddState( INT InID, wxBitmap* InBitmap );
	
	/**
	 * Return the current state, if any
	 *
	 * @return	The current state, if it has been set; NULL otherwise
	 */
	FBitmapStateButtonState* GetCurrentState();

	/**
	 * Set the current state to the state represented by the provided ID
	 *
	 * @param	InID	ID of the state to set as the current state
	 */
	void SetCurrentState( INT InID );

	/** If a current state is specified, cycle to the next bitmap state, wrapping once the end state has been hit */
	virtual void CycleState();

protected:
	/** States of the button */
	TArray<FBitmapStateButtonState*> States;

	/** Current state of the button */
	FBitmapStateButtonState* CurrentState;

private:
	/** 
	 * Called in response to a left mouse down action on the button, provided bCycleOnLeftMouseDown was set to TRUE during construction
	 *
	 * @param	In	Event automatically generated by wxWidgets upon left mouse down on the button
	 */
	void OnLeftButtonDown( wxMouseEvent& In );

	DECLARE_EVENT_TABLE()
};

/*-----------------------------------------------------------------------------
	WxBitmapCheckButton.

	A button that toggles between two states.
-----------------------------------------------------------------------------*/

class WxBitmapCheckButton : public WxBitmapStateButton
{
	DECLARE_DYNAMIC_CLASS(WxBitmapCheckButton);
public:
	WxBitmapCheckButton();
	WxBitmapCheckButton( wxWindow* InParent, wxWindow* InMsgTarget, wxWindowID InID, wxBitmap* InBitmapOff, wxBitmap* InBitmapOn, const wxPoint& InPos=wxDefaultPosition, const wxSize& InSize=wxDefaultSize  );
	~WxBitmapCheckButton();

	virtual void CycleState();

	// Declare an empty erase background callback to prevent flicker.
	void OnEraseBackground(wxEraseEvent& event) {};


	enum { STATE_Off, STATE_On };

	DECLARE_EVENT_TABLE()
};

