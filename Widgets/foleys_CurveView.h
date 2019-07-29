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

class CurveView   : public juce::Component,
                    public juce::ChangeBroadcaster
{
public:
    CurveView();

    /**
     Setting a pixel format will set the channel names and the colours per channel accordingly.
     You can override the default channel names and colours by calling @see setChannelNames()
     and @see setChannelColours().
     */
    void setPixelFormat (juce::Image::PixelFormat format);

    /**
     Set the channel names to display. They will be set by setPixelFormat, so if you want different
     names, you should call it after or instead of setPixelFormat.
     */
    void setChannelNames (const juce::StringArray& names);

    /**
     Set the channel colours to display. They will be set by setPixelFormat, so if you want different
     colours, you should call it after or instead of setPixelFormat.
     */
    void setChannelColours (const juce::Array<juce::Colour>& colours);

    /**
     Set the colour curves to use, e.g. when loading from a saved session.
     */
    void setColourCurves (std::vector<ColourCurve> colourCurves);

    /**
     Access the colour curves e.g. to apply to an Image @see applyLUTs()
     */
    const std::vector<ColourCurve>& getColourCurves() const;

    void paint (juce::Graphics& g) override;
    void resized() override;

private:

    void updateCurve (bool sendUpdate);

    juce::Image::PixelFormat pixelFormat;
    juce::StringArray channelNames;
    juce::Array<juce::Colour> channelColours;

    std::vector<ColourCurve> curves;
    juce::ComboBox channelSelect;
    juce::Rectangle<int> plotFrame;

    juce::Slider brightness { juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight };
    juce::Slider contrast { juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight };
    juce::Slider gamma { juce::Slider::LinearHorizontal, juce::Slider::TextBoxRight };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CurveView)
};

} // namespace foleys
