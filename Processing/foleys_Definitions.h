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
 */

#pragma once


namespace foleys
{

namespace Definitions
{

    static inline juce::StringArray getChannelNames (juce::Image::PixelFormat format)
    {
        switch (format)
        {
            case juce::Image::ARGB:
                return { NEEDS_TRANS ("Red"), NEEDS_TRANS ("Green"), NEEDS_TRANS ("Blue"), NEEDS_TRANS ("Alpha") };

            case juce::Image::RGB:
                return { NEEDS_TRANS ("Red"), NEEDS_TRANS ("Green"), NEEDS_TRANS ("Blue") };

            case juce::Image::SingleChannel:
                return { NEEDS_TRANS ("Alpha") };

            default:
                return {};
        }
    }

    static inline juce::Array<juce::Colour> getChannelColours (juce::Image::PixelFormat format)
    {
        switch (format)
        {
            case juce::Image::ARGB:
                return { juce::Colours::red, juce::Colours::green, juce::Colours::blue, juce::Colours::white };

            case juce::Image::RGB:
                return { juce::Colours::red, juce::Colours::green, juce::Colours::blue };

            case juce::Image::SingleChannel:
                return { juce::Colours::white };

            default:
                return {};
        }
    }
}

}
