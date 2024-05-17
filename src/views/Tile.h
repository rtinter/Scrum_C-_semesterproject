#include <string>
#include <imgui.h>

class Tile {
    int height;
    int width;
    ImVec4 color;
    std::string pictogram;
    std::string gameName;
    std::string description;

    // Setter-Methoden in den privaten Bereich verschieben
    void setHeight(int h);
    void setWidth(int w);
    void setPictogram(const std::string& pic);
    void setGameName(const std::string& name);
    void setDescription(const std::string& desc);

public:
    // Konstruktor
    Tile(int h, int w, ImVec4 c, const std::string& pic, const std::string& name, const std::string& desc);

    // Getter-Methoden
    int getHeight() const;
    int getWidth() const;
    const std::string& getPictogram() const;
    const std::string& getGameName() const;
    const std::string& getDescription() const;
    ImVec4 getColor() const;

    // Render-Methode
    void render();
};
