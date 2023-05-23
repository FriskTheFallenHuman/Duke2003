/*=============================================================================
	Controls.h: Misc custom/overridden controls.

	Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
=============================================================================*/

#ifndef __CONTROLS_H__
#define __CONTROLS_H__



UBOOL IsChildWindowOf (wxWindow* InChildWindow, wxWindow* InTestParentWindow);

/**
 * This class overrides the default constructor of wxRect to skip member initialization
 * This prevents default values from being overwritten in wxRect member variables of UObjects
 */
class WxRect : public wxRect
{
public:
	/** Default constructor */
	WxRect() : wxRect(x, y, width, height)
	{}

	/** Copy constructor */
	WxRect( const wxRect& Other )
	: wxRect(Other)
	{}
};

/*-----------------------------------------------------------------------------
	WxToolBar.
-----------------------------------------------------------------------------*/

/**
 * This class inherits from wxToolBar in order to provide tooltip functionality
 * beyond what is provided in the wxWidgets implementation. Tooltips for tools on 
 * wxToolBars display properly as long as the window with the toolbar has focus, but 
 * will not display if the window does not, contrary to how the rest of the tooltips 
 * provided by wxWidgets function. This is due to wxWidgets handling the tooltips of 
 * toolbar tools in a different manner that appears to be buggy. In lieu of modifying
 * the wxWidgets source and causing future version troubles, WxToolBar provides a 
 * low-impact solution to the problem until such time wxWidgets corrects the behavior 
 * by responding to the event generated when the mouse enters/exits a tool on the toolbar 
 * and setting the toolbar's tooltip itself accordingly (because tooltips set via 
 * SetToolTip work properly, even without focus). Additionally, the class disables the 
 * normal tooltip method for tools by forcibly passing in wxTB_NO_TOOLTIPS to the 
 * wxToolBar constructor, such that the two systems do not conflict.
 */
class WxToolBar : public wxToolBar
{
public:

	/** Default constructor; Required for 2-phase creation */
	WxToolBar() {}

	/**
	 * Constructor - Construct a WxToolBar object and hook up its event handler to respond
	 * to the mouse entering/exiting a tool on the toolbar.
	 *
	 * @param	InParent	Parent window of the toolbar
	 * @param	InId		Id to assign to the toolbar
	 * @param	InPos		Position to assign to the toolbar
	 * @param	InSize		Size to assign to the toolbar
	 * @param	InStyle		Window style to assign to the toolbar (forcibly made to include wxTB_NO_TOOLTIPS)
	 * @param	InName		Name to assign to the toolbar
	 */
	WxToolBar(	wxWindow *InParent, 
				wxWindowID InId, 
				const wxPoint& InPos = wxDefaultPosition, 
				const wxSize& InSize = wxDefaultSize, 
				LONG InStyle = wxTB_HORIZONTAL | wxTB_FLAT | wxTB_NO_TOOLTIPS, 
				const wxString &InName = wxToolBarNameStr );

	/**
	 * Initializes the toolbar when using two-stage dynamic window creation.  Must be the first function called after creation.
	 * NOTE: The underlying wxToolBar implementation of this function is NOT virtual. This should not be an issue given the
	 * context in which this function is used, but one must be careful to avoid behavior such as:
	 * wxToolBar *ToolBar = new WxToolBar; ToolBar->Create(...); // Note a wxToolBar pointer is used to create a WxToolBar object
	 *
	 * @param	InParent	Parent window of the toolbar
	 * @param	InId		Id to assign to the toolbar
	 * @param	InPos		Position to assign to the toolbar
	 * @param	InSize		Size to assign to the toolbar
	 * @param	InStyle		Window style to assign to the toolbar (forcibly made to include wxTB_NO_TOOLTIPS)
	 * @param	InName		Name to assign to the toolbar
	 *
	 * @return	TRUE if the toolbar was successfully created, FALSE otherwise
	 */
	UBOOL Create(	wxWindow *InParent, 
					wxWindowID InId, 
					const wxPoint& InPos = wxDefaultPosition, 
					const wxSize& InSize = wxDefaultSize, 
					LONG InStyle = wxTB_HORIZONTAL | wxTB_FLAT | wxTB_NO_TOOLTIPS, 
					const wxString &InName = wxToolBarNameStr );

private:

	/**
	 * Handles the mouse-over of a toolbar tool by setting the toolbar's tooltip to be that of the
	 * hovered over tool's.
	 *
	 * @param	In	Command event generated by wxWidgets when the mouse enters/exits a tool on the toolbar
	 */
	void OnToolEnter( wxCommandEvent& In );

	// Note: The following macro changes the access specifier to protected
	DECLARE_EVENT_TABLE();
};

/*-----------------------------------------------------------------------------
	WxStatusBar.
-----------------------------------------------------------------------------*/

/**
 * Baseclass for editor status bars.
 */
class WxStatusBar : public wxStatusBar
{
public:
	WxStatusBar();
	WxStatusBar( wxWindow* parent, wxWindowID id );

	/** 
	 * Sets the provided string to the status bar field at index 'i'
	 *
	 * @param text	New status field text.
	 * @param i		Field to set text to.
	 */

	virtual void SetStatusText( const wxString& text, int slotIdx )
	{
		wxStatusBar::SetStatusText(text, slotIdx);
	}

	virtual void SetUp()=0;
	virtual void UpdateUI()=0;

	/** Update the position and size of the status bar */
	virtual void RefreshPositionAndSize() = 0;

	// Standard StatusBar Specific Functions.

	/**
	 * Sets the mouse worldspace position text field to the text passed in.
	 *
	 * @param StatusText	 String to use as the new text for the worldspace position field.
	 */

	virtual void SetMouseWorldspacePositionText( const TCHAR* StatusText )
	{
		// Intentionally left empty.
	}

};


/*-----------------------------------------------------------------------------
	WxTextCtrl.
-----------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Helper class for static text to allow pass through
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WxPassThroughStaticText : public wxStaticText
{
public:
	WxPassThroughStaticText(wxWindow* InParent, wxWindowID InID, const wxString& InText)
		: wxStaticText (InParent, InID, InText)
	{

	}

	/**
	 * Event that simply passes the mouse event up to the parent
	 */
	void OnSkipMouseEvent(wxMouseEvent& In)
	{
		//pass up the chain
		In.ResumePropagation(wxEVENT_PROPAGATE_MAX);
		In.Skip(TRUE);
	}

	// Declare an empty erase background callback to prevent flicker.
	void OnEraseBackground(wxEraseEvent& event) {};
	
	DECLARE_EVENT_TABLE();
};


/*-----------------------------------------------------------------------------
	WxTextCtrl.
-----------------------------------------------------------------------------*/

/**
 * A drop-down text control.
 */
class WxTextCtrl : public wxTextCtrl, public wxDropTarget
{
public:
	WxTextCtrl();
	WxTextCtrl( wxWindow* parent,
				wxWindowID id,
				const wxString& value = TEXT(""),
				const wxPoint& pos = wxDefaultPosition,
				const wxSize& size = wxDefaultSize,
				long style = 0 );

	void OnChar( wxKeyEvent& In );

	virtual wxDragResult OnEnter(wxCoord x, wxCoord y, wxDragResult def);
	virtual void OnLeave();
	virtual wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def);

	DECLARE_EVENT_TABLE();
};

enum ENameValidationType
{
	VALIDATE_Name			=0x1,
	VALIDATE_ObjectName		=0x2,
	VALIDATE_GroupName		=0x4,
	VALIDATE_PackageName	=0x8,
};

/**
 * A text validator for text controls that are used to enter package and object names.  Prevents the user
 * from entering characters which are invalid in package/object names
 */
class WxNameTextValidator : public wxTextValidator
{
public:

	/**
	 * Constructor
	 *
	 * @param	StorageLocation		a pointer to a member of the owner window where the validated text will be placed
	 * @param	NameValidationMask	bitmask for the type of validation to apply
	 */
	WxNameTextValidator( wxString* StorageLocation, DWORD NameValidationMask=VALIDATE_PackageName );
};

/*-----------------------------------------------------------------------------
	WxPkgGrpNameCtrl.
-----------------------------------------------------------------------------*/

/**
 * A control that houses a collection of other controls designed to accept
 * a package/group(s)/name set of data from the user.
 */
class WxPkgGrpNameCtrl : public wxPanel
{
public:
	/** Derived classes wanting to add additional localized text should set bDeferLocalization to TRUE. */
	WxPkgGrpNameCtrl( wxWindow* parent, wxWindowID id, wxSizer* InParentSizer, UBOOL bDeferLocalization=FALSE );

	wxFlexGridSizer *FlexGridSizer;
	wxStaticText *PkgLabel, *GrpLabel, *NameLabel;
	wxComboBox *PkgCombo;
	wxTextCtrl *GrpEdit, *NameEdit;
	wxBitmapButton *BrowseButton;

	WxMaskedBitmap BrowseB;

	void EnablePackageCombo( UBOOL bEnablePackageCombo )
	{
		PkgCombo->Enable( !!bEnablePackageCombo );
	}

private:
	void OnBrowse( wxCommandEvent& In );

	DECLARE_EVENT_TABLE();
};

/*-----------------------------------------------------------------------------
	WxTreeCtrl.
-----------------------------------------------------------------------------*/

/**
 * An editor tree control.
 */ 
class WxTreeCtrl : public wxTreeCtrl
{
	DECLARE_DYNAMIC_CLASS(WxTreeCtrl)

	/**
	 * Flag to check for an item being selected during focus change
	 */
	UBOOL bInSetFocus;

	/**
	 * Intercepts the set focus call in order to trap the item selection
	 */
	virtual void SetFocus(void);

public:
	/** Default constructor for use in two-stage dynamic window creation */
	WxTreeCtrl() :
	  ContextMenu(NULL),
	  bInSetFocus(FALSE)
	{
	}

	WxTreeCtrl( wxWindow* InParent, wxWindowID InID, wxMenu* InMenu, LONG style=wxTR_HAS_BUTTONS | wxTR_MULTIPLE | wxTR_LINES_AT_ROOT );
	virtual ~WxTreeCtrl();

	/**
	 * Initializes this window when using two-stage dynamic window creation.  Must be the first function called after creation.
	 */
	virtual UBOOL Create( wxWindow* InParent, wxWindowID InID, wxMenu* InMenu, LONG style=wxTR_HAS_BUTTONS | wxTR_MULTIPLE | wxTR_LINES_AT_ROOT );

	/**
	 * Since we derive from wxTreeCtrl, the base code can't use the fast
	 * mechanism for sorting. Therefore, we provide this method to bypass
	 * the slower method.
	 *
	 * @param Item the tree item to sort
	 */
    void SortChildren(const wxTreeItemId& item);

	/**
	 * Accessor to the bInSetFocus property. Used to allow containers the option
	 * of cancelling the selection event
	 */
	UBOOL IsInSetFocus(void)
	{
		return bInSetFocus;
	}

	/**
	 * Sets all of the item's images to the same image.
	 *
	 *
	 * @param Item	Item to modify.
	 * @param Image	Index of the image in the tree control's image list.
	 */
	void SetAllItemImages(wxTreeItemId& Item, INT Image);

	/** 
	 * Loops through all of the elements of the tree and adds selected items to the selection set,
	 * and expanded items to the expanded set.
	 */
	virtual void SaveSelectionExpansionState();

	/** 
	 * Loops through all of the elements of the tree and sees if the client data of the item is in the 
	 * selection or expansion set, and modifies the item accordingly.
	 */
	virtual void RestoreSelectionExpansionState();

	void OnShowContextMenu( wxTreeEvent& Event );

protected:

	/** 
	 * Recursion function that loops through all of the elements of the tree item provided and saves their select/expand state. 
	 * 
	 * @param Item Item to use for the root of this recursion.
	 */
	void SaveSelectionExpansionStateRecurse(wxTreeItemId& Item);


	/** 
	 * Recursion function that loops through all of the elements of the tree item provided and restores their select/expand state. 
	 * 
	 * @param Item Item to use for the root of this recursion.
	 */
	void RestoreSelectionExpansionStateRecurse(wxTreeItemId& Item);

	/**
	 * Activates the context menu associated with this tree control.
	 *
	 * @param	ItemData	the data associated with the item that the user right-clicked on
	 */
	virtual void ShowPopupMenu( class WxTreeObjectWrapper* ItemData );

	/** Context menu associated with this tree control, displayed when the user right clicks on a tree control item. */
	wxMenu* ContextMenu;

	/** Saved state of client data objects that were selected. THESE VOID* POINTERS SHOULD ~NOT~ BE DEREFERENCED! */
	TMap<UObject*, UObject*> SavedSelections;

	/** Saved state of client data objects that were expanded. THESE VOID* POINTERS SHOULD ~NOT~ BE DEREFERENCED! */
	TMap<UObject*, UObject*> SavedExpansions;
};

/**
 * An implementation of WxTreeCtrl in which the popup menu appears only
 * when objects of a specific UObject-derived type are selected.
 */
template< class Type >
class WxTreeCtrlTyped : public WxTreeCtrl
{
public:
	WxTreeCtrlTyped( wxWindow* parent, wxWindowID id, wxMenu* InMenu )
		:	WxTreeCtrl( parent, id, InMenu )
	{}

protected:
	/**
	* Callback for wxWindows RMB events in which the popup menu appears only if
	* the click occured on an item of type Type.
	*/
	virtual void OnRightButtonDownCallback( wxMouseEvent& In )
	{
		wxTreeItemId id = HitTest( wxPoint( In.GetX(), In.GetY() ) );

		if( id > 0 )
		{
			class WxTreeObjectWrapper* ObjectWrapper = (WxTreeObjectWrapper*)GetItemData( id );
			if( ObjectWrapper )
			{
				// Only display the popup menu if the selected object is of the appropriate type.
				Type* SelectedObject = ObjectWrapper->GetObject<Type>();
				if ( SelectedObject )
				{
					ShowPopupMenu(ObjectWrapper);
				}
			}
		}
	}
};

/**
 * This class is used instead of the base wxWindow's class as it fixes some
 * bugs related to externally setting selection
 */
class WxComboBox : public wxComboBox
{
	DECLARE_DYNAMIC_CLASS(WxComboBox);

public:
	/**
	 * Ctor to match wxComboBox
	 */
	WxComboBox(void) : wxComboBox()
	{
	}

	/**
	 * Ctor to match wxComboBox
	 */
	WxComboBox(wxWindow *parent, wxWindowID id,
		const wxString& value = wxEmptyString,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		int n = 0, const wxString choices[] = NULL,
		long style = 0,
		const wxValidator& validator = wxDefaultValidator,
		const wxString& name = wxComboBoxNameStr) :
	wxComboBox(parent,id,value,pos,size,n,choices,style,validator,name)
	{
	}

	/**
	 * Ctor to match wxComboBox
	 */
	WxComboBox(wxWindow *parent, wxWindowID id,
		const wxString& value,
		const wxPoint& pos,
		const wxSize& size,
		const wxArrayString& choices,
		long style = 0,
		const wxValidator& validator = wxDefaultValidator,
			const wxString& name = wxComboBoxNameStr) :
		wxComboBox(parent,id,value,pos,size,choices,style,validator,name)
	{
	}

	/**
	 * This overload fixes a bug in the wxComboBox code where it doesn't
	 * properly update its internal state
	 *
	 * @param NewSelection the item that is to be selected
	 */
    virtual void SetSelection(int NewSelection)
	{
		wxComboBox::SetSelection(NewSelection);
	}

};

/**
 * wxListView class derivating with some added utility functionality to make it easier to work with the listview.
 */
class WxListView : public wxListView
{
public:
	WxListView(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxLC_ICON, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxListCtrlNameStr) : 
	  wxListView(parent, id, pos, size, style, validator, name)
	{

	}
	
	/**
	 * Returns the text of the item.
	 * @param Index Index of the item.
	 * @param Column Column of the item.
	 */
	wxString GetColumnItemText(long Index, long Column);
};

/**
 * Custom Class, a real number spinner control which is a combination of a textctrl and 2 buttons.
 */
class WxSpinCtrlReal : public wxPanel
{
public:
	WxSpinCtrlReal(wxWindow* parent, wxWindowID InID=wxID_ANY, FLOAT Value=0.0f, wxPoint Position=wxDefaultPosition, wxSize Size=wxDefaultSize, FLOAT InMinValue=-100000.0f, FLOAT InMaxValue=100000.0f);

	/**
	 * Sets a fixed increment amount to use instead of 1% of the current value.
	 * @param IncrementAmount	The increment amount to use instead of defaulting to 1% of the starting value.
	 */
	void SetFixedIncrementAmount(FLOAT IncrementAmount)
	{
		FixedIncrementAmount = IncrementAmount;
		bFixedIncrement = TRUE;
	}

	/**
	 * Changes the min value for this control
	 */
	void SetMinValue( const FLOAT NewMinValue, UBOOL bRevalidateCurrentValue=TRUE )
	{
		MinValue = NewMinValue;
		if ( bRevalidateCurrentValue )
		{
			SetValue(GetValue(), FALSE);
		}
	}

	/**
	 * Changes the max value for this control.
	 */
	void SetMaxValue( const FLOAT NewMaxValue, UBOOL bRevalidateCurrentValue=TRUE )
	{
		MaxValue = NewMaxValue;
		if ( bRevalidateCurrentValue )
		{
			SetValue(GetValue(), FALSE);
		}
	}

	/**
	 * @return	Returns the current value of the spin control.
	 */
	FLOAT GetValue() const;

	/**
	 * Sets the current value for the spin control.
	 *
	 * @param	Value		The new value of the spin control.
	 * @param	bSendEvent	Whether or not to send a SPIN event letting bound controls know that we changed value.
	 */
	void SetValue(FLOAT Value, UBOOL bSendEvent=FALSE);

protected:

	/**
	 * Updates the numeric property text box and sends the new value to all objects.
	 * @param NewValue New value for the property.
	 */
	void UpdatePropertyValue(FLOAT NewValue);

	/** Event handler for when the user enters text into the spin control textbox. */
	void OnText(wxCommandEvent &InEvent);

	/** Event handler for mouse events. */
	void OnMouseEvent(wxMouseEvent& InEvent);

	/** Event handler for the spin buttons. */
	void OnSpin(wxCommandEvent& InEvent);

	/** Sizing event handler. */
	void OnSize(wxSizeEvent &InEvent);


	/** Change since mouse was captured. */
	INT MouseDelta;

	wxPoint MouseStartPoint;

	/** Starting value of the property when we capture the mouse. */
	FLOAT StartValue;

	/** Min and Max value for the spinner. */
	FLOAT MinValue, MaxValue;

	/** Flag for whether or not we should be using a fixed increment amount. */
	UBOOL bFixedIncrement;

	/** Fixed increment amount. */
	FLOAT FixedIncrementAmount;

	/** Since Wx has no way of hiding cursors normally, we need to create a blank cursor to use to hide our cursor. */
	wxCursor BlankCursor;

	/** Text control that displays the current value of the spinner. */
	wxTextCtrl* TextCtrl;

	/** Sizer that holds the spinner buttons. */
	wxSizer* ButtonSizer;

	/** String for wxTextCtrl validator. */
	wxString ValidatorStringValue;

	DECLARE_EVENT_TABLE()
};

/**
 * Generates a cursor given only a local filename.  Uses the same mask as WxBitmap, (192,192,192).
 */
class WxCursor : public wxCursor
{
public:
	WxCursor(const char* Filename);
};

/**
 * Manages WxCursor objects so they are not loaded multiple times.
 */

class FCursorManager
{
public:
	static WxCursor& GetCursor(const ANSICHAR* Filename);
};


/**
 * FDeferredInitializationWindow, used by the property windows.
 */

class FDeferredInitializationWindow
{
	/** whether Create has been called on this window yet */
	UBOOL	bCreated;

public:
	FDeferredInitializationWindow()
		:	bCreated( FALSE )
	{}

	virtual ~FDeferredInitializationWindow() {}

	/** returns whether Create has been called on this window yet */
	UBOOL IsCreated() const
	{
		return bCreated;
	}

	/** Changes the value of bCreated to true...called when this window is created */
	void RegisterCreation()
	{
		bCreated = TRUE;
	}
};

/**
 * WxSearchControl: a combined filter/search text box and X button to clear the search.
 * 
 * Add an event such as EVT_TEXT(MY_SEARCHPANEL_ID,MyWindow::OnFilterChanged)
 */
class WxSearchControl : public wxControl, public FDeferredInitializationWindow
{
public :
	DECLARE_DYNAMIC_CLASS(WxSearchControl);
	virtual ~WxSearchControl(void);

	/**
	*	Initialize the search ctrl.  Must be the first function called after creation.
	*
	* @param	InParent		The parent window.
	* @param	InID			The wxWindowID to use for the the event notification.
	*/
	virtual void Create( wxWindow* InParent, wxWindowID InID );

	/**
	* Callback used for canceling searches
	*/
	void OnSearchButtonClicked ( wxCommandEvent& In );

	/** Rebuild the focus array to go through all open children */
	void AppendFocusWindows (OUT TArray<wxWindow*>& OutFocusArray);

	/**
	 * Force clears the filter string
	 */
	void ClearFilterString(void);

	/** Callback used to layout */
	void OnSize( wxSizeEvent& In );

	virtual wxSize DoGetBestSize() const;

	DECLARE_EVENT_TABLE();

protected:
	/** The text control used for the filter. */
	class WxSearchTextCtrl* FilterStringTextCtrl;
	/** Sizer used for laying out control */
	wxBoxSizer* FilterSizer;
};

class WxSearchControlNextPrev : public WxSearchControl
{
public:
	DECLARE_DYNAMIC_CLASS(WxSearchControlNextPrev);

	virtual void Create( wxWindow* InParent, wxWindowID InID );

	void EnableNextPrev( UBOOL bEnableNext, UBOOL bEnablePrev );

	virtual wxSize DoGetBestSize() const;

private:
	WxBitmap NextButtonImage;
	WxBitmap PrevButtonImage;
	wxBitmapButton* ButtonNext;
	wxBitmapButton* ButtonPrev;
};

#endif
