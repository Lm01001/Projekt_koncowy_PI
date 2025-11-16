#ifndef SLIDERSANDCHECKBOX_H
#define SLIDERSANDCHECKBOX_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/Renderers/CheckBoxRenderer.hpp>

    class SlidersAndCheckbox{
        public:
            int minVal, maxVal;
            float sliderVal;
            
            tgui::Slider::Ptr slider;
            tgui::Label::Ptr labelName;
            tgui::Label::Ptr labelVal;
            tgui::Label::Ptr labelMin;
            tgui::Label::Ptr labelMax;

            bool chosenCheckbox;
            tgui::CheckBox::Ptr checkboxLatwy;
            tgui::CheckBox::Ptr checkboxTrudny;
            tgui::Label::Ptr labelCheckBoxSection;

            SlidersAndCheckbox(int x, int y);
            void createSlider(int min, int max);
            void setSliderValue(float val);
            float getSliderVal();
            void dodajDoGui(tgui::Gui& gui);
            void usunZGui(tgui::Gui& gui);

            SlidersAndCheckbox(int x, int y, int textSize);
            void customLabelCreator(int x, int y);
            void dodajCheckbox(tgui::Gui& gui);
    };

#endif