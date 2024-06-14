
#include "ResultsScene.h"
#include "DashboardScene.hpp"
#include "SceneManager.hpp"
#include "Window.hpp"
#include "implot.h"

namespace scene {

    ResultsScene::ResultsScene() : _header("Meine Werte", "Home", [](){
        SceneManager::getInstance().switchTo(std::make_unique<DashboardScene>());
    }){
        //TODO Testdaten -> Hier Spieldaten einbinden!
        std::map<int, std::vector<std::string>> map;
        std::vector<std::string> stringvectorHeaderline {"Test", "Daten", "Für", "Tabelle"};
        std::vector<std::string> stringvectordata {"Heute", "Tom", "300 pkt", "win"};
        map[0] = stringvectorHeaderline;
        map[1] = stringvectordata;
        ui_elements::StatisticsGameTable coolTable{map};
        _results.addGameTableContainer(ui_elements::TableContainer("hallo", coolTable));
        _results.addGameTableContainer(ui_elements::TableContainer("hallo1", coolTable));
        _results.addGameTableContainer(ui_elements::TableContainer("hallo3", coolTable));
        _results.addGameTableContainer(ui_elements::TableContainer("hallo4", coolTable));
        _results.addGameTableContainer(ui_elements::TableContainer("hallo5", coolTable));
        _results.addGameTableContainer(ui_elements::TableContainer("hallo6", coolTable));

    }

    void drawPieChartToday(){
        static const char* labels[]    = {"Frogs","Hogs","Dogs","Logs"};
        static float data[]            = {0.15f,  0.30f,  0.2f, 0.05f};
        ImPlot::CreateContext();
        if (ImPlot::BeginPlot("##PieToday", ImVec2(250,250), ImPlotFlags_Equal | ImPlotFlags_NoMouseText)) {
            ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations);
            ImPlot::SetupAxesLimits(0, 1, 0, 1);
            ImPlot::PlotPieChart(labels, data, 4, 0.5, 0.5, 0.4, "%.2f", 90, ImPlotPieChartFlags_Normalize);
            ImPlot::EndPlot();
        }
        ImPlot::DestroyContext();
    }

    void drawPieChartTotal(){
        static const char* labels[]    = {"Frogs","Hogs","Dogs","Logs"};
        static float data[]            = {0.15f,  0.30f,  0.2f, 0.05f};
        ImPlot::CreateContext();
        if (ImPlot::BeginPlot("##PieTotal", ImVec2(250,250), ImPlotFlags_Equal | ImPlotFlags_NoMouseText)) {
            ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations);
            ImPlot::SetupAxesLimits(0, 1, 0, 1);
            ImPlot::PlotPieChart(labels, data, 4, 0.5, 0.5, 0.4, "%.2f", 90, ImPlotPieChartFlags_Normalize);
            ImPlot::EndPlot();
        }
        ImPlot::DestroyContext();
    }

    void ResultsScene::render() {
        ui_elements::Window("Result").render([this] {
            _header.render();
            drawPieChartToday();
            drawPieChartTotal();
            _results.render();
        });
    }

    std::string ResultsScene::getName() const {
        return "ResultsScene";
    }
} // scene