/***************************************************************************
 * Copyright (c) 2024 Microsoft Corporation
 * Copyright (c) 2026 Eclipse ThreadX contributors
 *
 * This program and the accompanying materials are made available under the
 * terms of the MIT License which is available at
 * https://opensource.org/licenses/MIT.
 *
 * SPDX-License-Identifier: MIT
 **************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** GUIX Component                                                        */
/**                                                                       */
/**   System Management (System)                                          */
/**                                                                       */
/**************************************************************************/

#define GX_SOURCE_CODE


/* Include necessary system files.  */

#include "gx_api.h"
#include "gx_system.h"
#include "gx_window.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _gx_system_all_views_free                           PORTABLE C      */
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Kenneth Maxwell, Microsoft Corporation                              */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function releaes the views attached to the given root window   */
/*    and it's chilren back to the free list.                             */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    root                                  Root window that needs to     */
/*                                            have it's views released    */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    views owned by this root and children are returned to free list     */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*     _gx_system_views_free                Free views for one window     */
/*     _gx_system_error_process             Process error code            */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    GUIX Internal Code                                                  */
/*                                                                        */
/**************************************************************************/
VOID _gx_system_all_views_free(GX_WINDOW_ROOT *root)
{
#ifndef GX_DISABLE_ERROR_CHECKING
int viewcount;
GX_VIEW   *test;
#endif

GX_WIDGET *child;

    /* pick up pointer to first child window */
    child = root -> gx_widget_first_child;

    /* free each of the top-level window's views */
    while (child)
    {
        if (child -> gx_widget_type >= GX_TYPE_WINDOW)
        {
            _gx_window_view_free((GX_WINDOW *)child);
        }
        child = (child -> gx_widget_next);
    }

    /* lastly, free the root window's views */
    _gx_window_view_free((GX_WINDOW *)root);

#ifndef GX_DISABLE_ERROR_CHECKING
    test = _gx_system_free_views;

    viewcount = 0;

    while (test)
    {
        viewcount++;
        test = test -> gx_view_next;
    }

    if (viewcount != GX_MAX_VIEWS)
    {
        _gx_system_error_process(GX_SYSTEM_OUT_OF_VIEWS);
    }
#endif
}

