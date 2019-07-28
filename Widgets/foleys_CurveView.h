
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
