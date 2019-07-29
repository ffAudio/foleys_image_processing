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

/*
 This class will display the histogram of a given Image
 */
class HistogramView    : public juce::Component
{
public:
    HistogramView() = default;

    /**
     Setting a pixel format will set the channel names and the colours per channel accordingly.
     You can override the default channel names and colours by calling @see setChannelNames()
     and @see setChannelColours().
     */
    void setPixelFormat (juce::Image::PixelFormat format);

    /**
     Set the histogram data to display.
     @param histogram is a vector containing a vector per channel holding the sum of pixels per value
     @param max is the maximum number of pixels to display. width * height / 64 seems to be a good value.
     */
    void setHistogram (std::vector<std::vector<unsigned int>> histogram, unsigned int max);

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

    void paint (juce::Graphics&) override;

private:

    void drawHistogramChart (juce::Graphics& g, std::vector<unsigned int> bins, unsigned int max, juce::Rectangle<float> bounds, juce::Colour colour);

    juce::Image::PixelFormat pixelFormat;
    juce::StringArray channelNames;
    juce::Array<juce::Colour> channelColours;

    std::vector<std::vector<unsigned int>> histogram;
    unsigned int maxNumberPixels = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HistogramView)
};

} // namespace foleys
