

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

    void setPixelFormat (juce::Image::PixelFormat format);
    void setHistogram (std::vector<std::vector<unsigned int>> histogram);

    void setChannelNames (const juce::StringArray& names);
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
