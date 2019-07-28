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

    void setPixelFormat (juce::Image::PixelFormat format);
    void setChannelNames (const juce::StringArray& names);
    void setChannelColours (const juce::Array<juce::Colour>& colours);

    void paint (juce::Graphics& g) override;
    void resized() override;

    const std::vector<ColourCurve>& getColourCurves() const;

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
