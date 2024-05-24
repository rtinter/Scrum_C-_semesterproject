//
// Created by zarathustra on 23.05.24.
//

#ifndef INFOBOX_H
#define INFOBOX_H


namespace ui_elements {
    class InfoBox {

        const char *_game_name;
        const char *_game_descr;
        const char *_game_rules;
        const char *_game_controls;

    public:
        void render();
        InfoBox(const char *game_name, const char *game_descr, const char *game_rules, const char *game_controls);

    };
}

#endif //INFOBOX_H
