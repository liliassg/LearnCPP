#pragma once
#include<stdint.h>
#include<vector>
#include<string>
#include<iostream>

namespace util {
    // Slice a Vector and get its n elements from begin (eg. what=3, returns 0, 1, 2)
    std::vector<int> getIndexesOfVector(std::vector<int>& vec, int what) {
        size_t sizeofVec = vec.size();
        std::vector<int> indexes{};
        for (int i = 0; i < what || i <= sizeofVec; i++) {
            indexes.push_back(vec.at(i));
        }
        if (what > indexes.size()) {
            std::cout << "util::getIndexesOfVector: error returning requested sizes '" << what << "' vector is too tiny!" << std::endl;
            for (int missing = what - indexes.size(); missing >= indexes.size(); missing++) { // flood missing indexes to prevent segfault
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
        WHITE
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
   // createColorByInt: 
    static Color createColorByInt(int r, int g, int b) {}
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
    Style style;
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
    // Structure an Segment Drawer, to store written Text by position inside the box
    struct SegmentDrawer {
        std::string text{};
        Position textPos{};
    };
    // Structure an Box, the actual renderd logic for texts
    struct Box {
        Size size{};
        Offset offset{};
        int innerWidthSpace{}; // represent the maximum space of lines fitting Vertical inside the box, determined by width*height*offsetX
        int innerHeightSpace{}; // represent the maximum space of lines fitting Horizontal inside the box, determined by width*height*offsetY
        std::vector<SegmentDrawer> segmentContent{};
        Style::Color background{};
    };
    // Structure an Segment (used for defining an Box within the console for drawning inside)
    struct Segment {
        std::string initalID{};
        Position location{};
        Box box{};
        bool visible{};
    };
    // Structure the Layout (used for the Terminals Draw behaviour)
    struct Layout {
        Style::Color background;
        std::vector<Segment> segments;
    };
    /*
        Classdef Methods
    */
    // getColorSequence: used by getSequence to determine Color
    std::string getColorSequence(Style::Color) {}
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
                return nullptr;
        }
    }
    // setCursor: set the console-cursor to a position {x, y}
    void setCursor(Position location) {}
    // createColor: create an Color object
    // createPosition: create an Position object
    static Position createPosition(int x = 0, int y = 0) {}
    // createSize: create an Size object  
    static Size createSize(int height, int length) {}
    // createOffset: create an Offset object
    static Offset createOffset(int x, int y) {}
    // createSegment: create an Segment object
    Segment createSegment(std::string id, Position pos = {0, 0}, Size box = {0, 0}, Offset offset = {10, 10}) {
        Segment segment{};
        segment.initalID = id;

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
        Segment Methods
    */
    void segmentWriteText(Segment& seg, std::string text, Position startingPos) { SegmentDrawer segmentEntity{}; }
    void segmentWriteLines(Segment& seg, std::vector<std::string> lines, Position startingPos) {}
    void segmentAddText(Segment& seg, std::string text) {}
    void segmentAddLines(Segment& seg, std::vector<std::string> lines) {}
    void segmentClear(Segment& seg) {}
    void segmentModify(Segment& seg, Position newPos, Size newBox, Offset newOffset) {}
    /*
        Box Render Methods
    */
    int boxCalculateInnerWidthSpace(const Box segbox) {}
    int boxCalculateInnerHeightSpace(const Box segbox) {}
};
}