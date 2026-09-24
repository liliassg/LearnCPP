#pragma once
#include<stdint.h>
#include<vector>
#include<string>
#include<string_view>
#include<iostream>

namespace util {
    // Slice a Vector and get its n elements from begin (eg. what=3, returns 0, 1, 2)
    inline std::vector<int> getIndexesOfVector(std::vector<int>& vec, const int what) {
        size_t sizeofVec = vec.size();
        std::vector<int> indexes{};
        for (int i = 0; i < what && i < sizeofVec; i++) {
            indexes.push_back(vec.at(i));
        }
        if (what > indexes.size()) {
            std::cout << "util::getIndexesOfVector: error returning requested sizes '" << what << "' vector is too tiny!" << std::endl;
            while (what > indexes.size()) { // flood missing indexes to prevent segfault
                indexes.push_back(0);
            }
        }
        return indexes;
    }

}

namespace UI {

class Style {
    public:
    // Handle a bunch of Color RGB Sequences
    enum class ColorRGB {
        RED,
        DARK_RED,
        LIGHT_RED,
        MAGENTA,
        LILA,
        PINK,

        GREEN,
        DARK_GREEN,
        LIGHT_GREEN,
        LIME,

        BLUE,
        LIGHT_BLUE,
        DARK_BLUE,
        CYAN,

        YELLOW,
        LIGHT_YELLOW,
        DARK_YELLOW,
        GOLD,

        ORANGE,
        LIGHT_ORANGE,
        DARK_ORANGE,

        GRAY,
        LIGHT_GRAY,

        BLACK,
        WHITE,

        DEFAULT
    };
    // Structure an Color (used for Style Text within the console)
    struct Color {
        ColorRGB enumCol;
        uint8_t r{};
        uint8_t g{};
        uint8_t b{};
    };
    /*
        Color Methods
    */
   // createColorByInt: create ab Color object, by passing r, g, b as integers
    static Color createColorByInt(int r, int g, int b) {}
// createColor: create an Color object by passing enum Style::ColorRGB
    static Color createColor(Style::ColorRGB col) {
        Color colorObject{};
        colorObject.enumCol = col;
        switch (col) {
            case ColorRGB::RED:
                break;
            case ColorRGB::LIGHT_RED:
                break;
            case ColorRGB::DARK_RED:
                break;
            case ColorRGB::MAGENTA:
                break;
            case ColorRGB::LILA:
                break;
            case ColorRGB::PINK:
                break;
            case ColorRGB::GREEN:
                break;
            case ColorRGB::DARK_GREEN:
                break;
            case ColorRGB::LIGHT_GREEN:
                break;
            case ColorRGB::LIME:
                break;
            case ColorRGB::BLUE:
                break;
            case ColorRGB::LIGHT_BLUE:
                break;
            case ColorRGB::DARK_BLUE:
                break;
            case ColorRGB::CYAN:
                break;
            case ColorRGB::YELLOW:
                break;
            case ColorRGB::LIGHT_YELLOW:
                break;
            case ColorRGB::DARK_YELLOW:
                break;
            case ColorRGB::GOLD:
                break;
            case ColorRGB::ORANGE:
                break;
            case ColorRGB::LIGHT_ORANGE:
                break;
            case ColorRGB::DARK_ORANGE:
                break;
            case ColorRGB::GRAY:
                break;
            case ColorRGB::LIGHT_GRAY:
                break;
            case ColorRGB::BLACK:
                break;
            case ColorRGB::WHITE:
                break;
            default:
                std::cout << "unkown color!\n";
                colorObject.b = -1;
                colorObject.g = -1;
                colorObject.r = -1;
                break;
        }
        return colorObject;
    }
};

class Terminal {
    public:
    /*
        Class Globals
    */
    // Handle any type of ANSI Escape Sequences
    enum class ANSI_SEQUENCES {
        COLOR,
        CLEAR,
        CURSOR
    };
    // Structure an Position 
    struct Position {
        int x{};
        int y{};
    };
    // Structure an Size
    struct Size {
        int width{};
        int height{};
    };
    // Structure an Offset
    struct Offset {
        int offsetX{};
        int offsetY{};
    };
    // Structure an Segment Text, to store written Text by position inside the box
    struct SegmentText {
        std::string initialID{};
        std::string text{};
        Position textPos{};
        Style::Color background{};
    };
    // Structure an Box, the actual renderd logic for texts
    struct Box {
        Size size{};
        Offset offset{};
        int innerWidthSpace{}; // represent the maximum space of lines fitting Vertical inside the box, determined by width*height*offsetX
        int innerHeightSpace{}; // represent the maximum space of lines fitting Horizontal inside the box, determined by width*height*offsetY
        std::vector<SegmentText> segmentContent{};
        Style::Color background{};
    };
    // Structure an Segment (used for defining an Box within the console for drawning inside)
    struct Segment {
        std::string initialID{};
        Position location{};
        Box box{};
        bool visible{};
    };
    // Structure the Layout (used for the Terminals Draw behaviour)
    struct Layout {
        Style::Color background;
        std::vector<Segment> segments;
        bool visable{};
    };
    /*
        Class globals (after structures)
    */
    Layout* mainLayout{}; 
    /*
        Classdef Methods
    */
    // getColorSequence: used by getSequence to determine Color
    std::string getColorSequence(Style::Color) {}
    // allEqualTo: is a helper made to check if all values are the same, for eg. defaulkts like -1, if all are -1 then it should be a non-set
    bool allEqualTo(std::vector<int> defaults) {
        int first{};
        for (int i = 0; i < defaults.size(); i++) {
            if (i == 0) {
                first = defaults[0];
                continue;
            }
            if (first != defaults[i]) {
                return false;
            }
        }
        return true;
    }
    // allEqualTo(2): is a helper made to check if all values are the same, specified by a defaultValue
    bool allEqualTo(std::vector<int> defaults, int defaultValue) {
        int first = defaultValue;
        for (int i = 0; i < defaults.size(); i++) {
            if (first != defaults[i]) {
                return false;
            }
        }
        return true;
    }
    // getSequence: get an ANSI escape sequence by sepecify sequence and pass a vector of integars
    std::string getSequence(ANSI_SEQUENCES seq, std::vector<int>& intData) {
        size_t passedDataSize = intData.size();
        std::vector<int> usedData{};
        switch (seq) {
            case ANSI_SEQUENCES::CLEAR:
                //! impl
                break;
            case ANSI_SEQUENCES::COLOR:
                usedData = util::getIndexesOfVector(intData, 3);    
                return getColorSequence(Style::createColorByInt(usedData.at(0), usedData.at(1), usedData.at(2)));
                break;
            case ANSI_SEQUENCES::CURSOR:
                //! impl
                break;
            default:
                std::cout << "unkown enumtype ansi sequence\n";
                return "";
        }
    }
    // setCursor: set the console-cursor to a position {x, y}
    void setCursor(Position location) {}
    // createLayout: create an Layout Object (the main widget all Segments are attached to)
    Layout createLayout(Style::ColorRGB color = Style::ColorRGB::DEFAULT) {
        Layout newLayout;
        Style::Color col = Style::createColor(color);
        if (allEqualTo({col.r, col.g, col.b}, -1)) {
            return newLayout;
        }
        newLayout.background = col;
        return newLayout;
    }
    // createPosition: create an Position object
    static Position createPosition(int x = 0, int y = 0) {
        Position posObj{x, y};
        return posObj;
    }
    // createSize: create an Size object  
    static Size createSize(int height, int width) {
        Size sizeObj;
        sizeObj.height = height;
        sizeObj.width = width;
        return sizeObj;
    }
    // createOffset: create an Offset object
    static Offset createOffset(int x, int y) {
        Offset offsetObj{x, y};
        return offsetObj;
    }
    // createSegment: create an Segment object
    Segment createSegment(const std::string_view id, Position pos = {0, 0}, Size box = {0, 0}, Offset offset = {10, 10}) {
        Segment segment{};
        segment.initialID = id;

        segment.location.x = pos.x;
        segment.location.y = pos.y;

        segment.box.size.width = box.width;
        segment.box.size.height = box.height;

        segment.box.offset.offsetX = offset.offsetX;
        segment.box.offset.offsetY = offset.offsetY;

        segment.box.innerWidthSpace = boxCalculateInnerWidthSpace(segment.box);
        segment.box.innerHeightSpace = boxCalculateInnerHeightSpace(segment.box);

        return segment;
    }
    /*
        Layout Methods
    */
   // layoutAddSegment: save a Segment into the Layout, returns adress of stored Segment
    Segment& layoutAddSegment(Layout& layout, Segment& seg) {
        layout.segments.push_back(std::move(seg));
        return layout.segments.back();
    }
    // layoutGetSegment: returns the Adress of an Segment specified by the Segment ID
    Segment* layoutGetSegment(Layout& layout, std::string_view segmentID) {
        for (auto& s : layout.segments) {
            if (s.initialID == segmentID) {
                return &s;
            }
        }
        return nullptr;
    }
    // layoutRemoveSegment: removes an Segment from the Layout, specified by the Segment ID
    void layoutRemoveSegment(Layout& layout, std::string_view segmentID) {
        for (int i = 0; i < layout.segments.size(); i++) {
            if (layout.segments[i].initialID == segmentID) {
                layout.segments.erase(layout.segments.begin() + i);
                return;
            }
        }
        std::cout << "layoutRemoveSegment: operation failed. Segment with id: " << segmentID << " was not found!\n";
        return;
    }
    // layoutVisable: set your layout as the main-rendered-layout 
    void layoutSetVisable(Layout& layout) {
        mainLayout = &layout;
        return;
    }
    /*
        Segment Methods
    */
   // segmentWriteText: create a new SegmentText object and pass it into the Segment
    void segmentWriteText(const std::string_view textID, Segment& seg, std::string text, Position startingPos = {0, 0}) { 
        SegmentText segmentText{}; 
        segmentText.textPos = startingPos;
        segmentText.text = text;
        segmentText.initialID = textID;
        seg.box.segmentContent.push_back(segmentText);
   }
    // segmentWriteLines: create a new SegmentText object and pass it into the Segment
    void segmentWriteLines(Segment& seg, const std::string_view textID, std::vector<std::string> lines, Position startingPos = {0, 0}) {  
        SegmentText segmentText{};
        segmentText.textPos = startingPos;
        segmentText.initialID = textID;
        for (int i = 0; i < lines.size(); i++) {
            segmentText.text += lines.at(i);
        }
        seg.box.segmentContent.push_back(segmentText);
    }
    // segmentAddText: write text into an existing SegmentText object, specified by its ID
    void segmentAddText(Segment& seg, const std::string_view textID, std::string text) {
        int pos = getSegmentTextIDIndex(seg, textID);
        if (pos == -1) {
            std::cout << "segmentAddText: operation failed, no such textID: " << textID << "\n";
            return;
        }
        seg.box.segmentContent[pos].text += text;
    }
    // segmentAddLines: write text into an existing SegmentText object, specified by its ID
    void segmentAddLines(Segment& seg, const std::string_view textID, std::vector<std::string> lines) {
        int pos = getSegmentTextIDIndex(seg, textID);
        if (pos == -1) {
            std::cout << "segmentAddLines: operation failed, no such textID: " << textID << "\n";
            return;
        }
        for (int i = 0; i < lines.size(); i++) {
            seg.box.segmentContent[pos].text += lines.at(i);
        }
    }
    // segmentClear: clear text on an SegmentText, specified by an textID, or none to clear it fully
    void segmentClear(Segment& seg, const std::string_view textID = "NONE@NULL") {
        if (textID == "NONE@NULL") {
            seg.box.segmentContent.clear();
            return;
        }
        int pos = getSegmentTextIDIndex(seg, textID);
        if (pos == -1) {
            std::cout << "segmentClear: operation failed, no such textID: " << textID << "\n";
            return;
        }
        seg.box.segmentContent[pos].text.clear();
        return;
    }
    // segmentModify: modify an Segment's data, pass only the needed modifications, required, eg. segmentModify(myseg, newSize={100, 100});
    void segmentModify(Segment& seg, Position newPos = {-1, -1}, Size newSize = {-1, -1}, Offset newOffset = {-1, -1}) {
        if (!allEqualTo({newPos.x, newPos.y}, -1)) {
            seg.location.x = newPos.x;
            seg.location.y = newPos.y;
        }
        if (!allEqualTo({newOffset.offsetX, newOffset.offsetY}, -1)) {
            seg.box.offset.offsetX = newOffset.offsetX;
            seg.box.offset.offsetY = newOffset.offsetY;
            seg.box.innerHeightSpace = boxCalculateInnerHeightSpace(seg.box);
            seg.box.innerWidthSpace = boxCalculateInnerWidthSpace(seg.box);
        }
        if (!allEqualTo({newSize.height, newSize.width}, -1)) {
            seg.box.size.height = newSize.height;
            seg.box.size.width = newSize.width;
        }
        return; 
    }
    // segmentVisable: determine if a Segment is visable or not
    void segmentVisable(Segment& seg, const bool status) {
        seg.visible = status;
    }
    void segmentSetBackground(Segment& seg, Style::ColorRGB color) {
        Style::Color col = Style::createColor(color);
        if (allEqualTo({col.r, col.g, col.b}, -1)) {
            return;
        }
        seg.box.background = col;
    }
    /*
        Segment Methods: 
            *SegmentText
    */
   // getSegmentTextIDIndex: get index of the SegmentTextID inside the Segment, returns -1 if not found
    int getSegmentTextIDIndex(const Segment& seg, const std::string_view searchedID) {
        for (int i = 0; i < seg.box.segmentContent.size(); i++) {
            if (seg.box.segmentContent.at(i).initialID == searchedID) {
                return i;
            }
        }
        return -1;
    }
    void setSegmentTextBackground(Segment& seg, std::string_view textID, Style::ColorRGB color) {
        int pos = getSegmentTextIDIndex(seg, textID);
        if (pos == -1) {
            std::cout << "setSegmentTextBackground: operation failed! no such textID: " << textID << "\n";
            return;
        }
        Style::Color col = Style::createColor(color);
        if (allEqualTo({col.r, col.g, col.b}, -1)) {
            return;
        }
        seg.box.segmentContent[pos].background = col;
    }
    /*
        Box Render Methods
    */
    int boxCalculateInnerWidthSpace(const Box segbox) {}
    int boxCalculateInnerHeightSpace(const Box segbox) {}
};
}