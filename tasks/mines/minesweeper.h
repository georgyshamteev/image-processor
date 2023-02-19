#pragma once

#include <string>
#include <vector>
#include <set>

class Minesweeper {
public:
    struct Cell {
        size_t x = 0;
        size_t y = 0;
    };

    struct GameCell {
        bool isflag = false;
        bool ismine = false;
        bool isopen = false;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    using RenderedField = std::vector<std::string>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    GameStatus GetGameStatus() const;
    time_t GetGameTime() const;

    RenderedField RenderField() const;

private:
    using Board = std::vector<std::vector<GameCell>>;
    Board board_;
    GameStatus game_status_ = GameStatus::NOT_STARTED;
    time_t time_from_start_ = 0;
    time_t time_ans_ = 0;
    size_t width_;
    size_t height_;
    size_t cells_to_open_;
    std::set<std::pair<size_t, size_t>> used_;
    std::pair<std::vector<std::pair<size_t, size_t>>, size_t> CheckNbr_(size_t y, size_t x) const;
};
