/*
 ==============================================================================

    Copyright (c) 2019, Foleys Finest Audio - Daniel Walz
    All rights reserved.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
    IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
    OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
    OF THE POSSIBILITY OF SUCH DAMAGE.

 ==============================================================================

    The block below describes the properties of this module, and is read by
    the Projucer to automatically generate project code that uses it.
    For details about the syntax and how to create or use a module, see the
    JUCE Module Format.txt file.

    BEGIN_JUCE_MODULE_DECLARATION

    ID:               foleys_image_processing
    vendor:           Foleys Finest Audio
    version:          1.0.0
    name:             Foleys Finest Image Processing
    description:      A collection to do image processing and some widgets to inspect and modify image data
    website:          https://foleysfinest.com
    license:          BSD 3-clause

    dependencies:     juce_core, juce_graphics, juce_gui_basics

    END_JUCE_MODULE_DECLARATION

 ==============================================================================
 */

#pragma once

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "Processing/foleys_Definitions.h"
#include "Processing/foleys_ColourLookuptables.h"
#include "Processing/foleys_ImageProcessing.h"
#include "Widgets/foleys_HistogramView.h"
#include "Widgets/foleys_CurveView.h"
