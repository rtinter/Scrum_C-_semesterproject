//
// Created by zarathustra on 23.05.24.
//

#ifndef INFOBOX_H
#define INFOBOX_H


namespace ui_elements {
    class InfoBox {
    public:
        const char *_name;
        const char *_game_descr;
        const char *_game_rules;
        const char *_game_controls;
        InfoBox(const char *game_name, const char *game_descr, const char *game_rules, const char *game_controls);
    public:
        void render();

    };
}

#endif //INFOBOX_H
