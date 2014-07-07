/** @file HiiTest.c
   
  HII test application
  
**/

/*=============================================================================
                              EDIT HISTORY

  $Header: 
  $DateTime: 2012-02-13 00:26:40 $ 
  $Author: William.L $ 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/13/12   William.L    Init.

=============================================================================*/

/*=========================================================================
      Include Files
==========================================================================*/
#include "HiiTestData.h"
#include "HiiTest.h"

/*=========================================================================
      Type Definitions
==========================================================================*/
EFI_GUID   mFormSetGuid = HII_TEST_FORM_GUID;

/*=========================================================================
      Function Prototypes
==========================================================================*/


/*=========================================================================
      Functions
==========================================================================*/
/**
  Test HiiTest application entry point. 

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

EFI_STATUS
EFIAPI
HiiTestMain (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                      Status;
  EFI_HII_HANDLE                  HiiHandle;
  EFI_SCREEN_DESCRIPTOR           Screen;
  EFI_HII_DATABASE_PROTOCOL       *HiiDatabase;
  EFI_HII_STRING_PROTOCOL         *HiiString;
  EFI_FORM_BROWSER2_PROTOCOL      *FormBrowser2;
  CHAR16                          *NewString, *NewString2;
  UINTN                           BufferSize;
  BOOLEAN                         ActionFlag;
  EFI_STRING                      ConfigRequestHdr;
  //  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ForeGround;
  //  EFI_GRAPHICS_OUTPUT_BLT_PIXEL BackGround;  
  
  TEST_START("HiiTest");
  
  SystemTable->ConOut->ClearScreen(SystemTable->ConOut);  /* Clear screen */

  /* 1. */
  //
  // Initialize screen dimensions for SendForm().
  // Remove 3 characters from top and bottom
  //
  ZeroMem (&Screen, sizeof (EFI_SCREEN_DESCRIPTOR));
  gST->ConOut->QueryMode (gST->ConOut, gST->ConOut->Mode->Mode, &Screen.RightColumn, &Screen.BottomRow);
  Screen.TopRow     = 3;
  Screen.BottomRow  = Screen.BottomRow - 3;

  /* 2. */
  //
  // Locate Hii Database protocol
  //
  Status = gBS->LocateProtocol (&gEfiHiiDatabaseProtocolGuid, NULL, (VOID **) &HiiDatabase);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  /* 3. */
  //
  // Locate HiiString protocol
  //
  Status = gBS->LocateProtocol (&gEfiHiiStringProtocolGuid, NULL, (VOID **) &HiiString);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  
  /* . */
  //
  // Locate Formbrowser2 protocol
  //
  Status = gBS->LocateProtocol (&gEfiFormBrowser2ProtocolGuid, NULL, (VOID **) &FormBrowser2);
  if (EFI_ERROR (Status)) {
    return Status;
  }  
  
  /* . */
  //
  // Publish our HII data
  //
  HiiHandle = HiiAddPackages (
                   &mFormSetGuid,
                   NULL,  /* Device handle */
                   HiiTestStrings,
                   HiiTestVfrBin,
                   NULL
                   );

  ASSERT (HiiHandle != NULL);

  //
  // Very simple example of how one would update a string that is already
  // in the HII database
  //
  NewString = L"New String - This is a basic HII programming test";
  if (HiiSetString (HiiHandle, STRING_TOKEN(STR_HIITEST_FORM_SET_HELP), NewString, NULL) == 0) {

    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Very simple example of how to create a new string 
  //
  NewString2 = L"2nd New String - This is a basic HII programming test";
  HiiSetString (HiiHandle, 0, NewString2, NULL);
    
  //
  // Example of how to display only the item we sent to HII
  // When this driver is not built into Flash device image,
  // it need to call SendForm to show front page by itself.
  //
  if (1) {
    //
    // Have the browser pull out our copy of the data, and only display our data
    //
    Status = FormBrowser2->SendForm (
                             FormBrowser2,
                             &HiiHandle,
                             1,
                             &mFormSetGuid, /* Form GUID */
                             0, 			/* Form ID */
                             &Screen,
                             NULL
                             );

    HiiRemovePackages (HiiHandle);
  }
  
  TestStatus("HiiTestApp", EFI_SUCCESS);
  TEST_STOP("HiiTestApp");
  
  return EFI_SUCCESS;
}

