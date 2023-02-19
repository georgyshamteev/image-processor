#include "minesweeper.h"

#include <set>
#include <random>
#include <ctime>
#include <deque>
#include <iostream>

bool Mycomp(const std::pair<size_t, std::pair<size_t, size_t>>& lhv,
            const std::pair<size_t, std::pair<size_t, size_t>>& rhv) {
    return lhv.first < rhv.first;
}

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    NewGame(width, height, mines_count);
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    NewGame(width, height, cells_with_mines);
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    board_.clear();
    width_ = width;
    height_ = height;
    cells_to_open_ = width * height - mines_count;
    game_status_ = GameStatus::NOT_STARTED;
    used_.clear();
    std::vector<std::pair<size_t, std::pair<size_t, size_t>>> cell_cet;

    std::random_device rd;
    std::mt19937 rng(rd());
    const size_t high = cell_cet.size() * 10;
    for (size_t h = 0; h < height; ++h) {
        std::vector<GameCell> vt;
        for (size_t w = 0; w < width; ++w) {
            vt.push_back(GameCell{false, false, false});
            std::uniform_int_distribution<int> uni(0, static_cast<int>(high));
            size_t n = uni(rng);
            cell_cet.push_back(std::make_pair(n, std::make_pair(h, w)));
        }
        board_.push_back(vt);
    }

    std::sort(cell_cet.begin(), cell_cet.end(), Mycomp);

    size_t cnt = 0;

    while (cnt < mines_count) {
        size_t y = cell_cet[cnt].second.second;
        size_t x = cell_cet[cnt].second.first;
        board_[y][x].ismine = true;
        ++cnt;
    }
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    board_.clear();
    width_ = width;
    height_ = height;
    cells_to_open_ = width * height - cells_with_mines.size();
    game_status_ = GameStatus::NOT_STARTED;
    used_.clear();
    for (size_t h = 0; h < height; ++h) {
        std::vector<GameCell> vt;
        for (size_t w = 0; w < width; ++w) {
            vt.push_back(GameCell{false, false, false});
        }
        board_.push_back(vt);
    }

    for (size_t h = 0; h < height; ++h) {
        for (size_t w = 0; w < width; ++w) {
            board_[h][w].ismine = false;
        }
    }
    for (auto cell : cells_with_mines) {
        board_[cell.y][cell.x].ismine = true;
    }
}

std::pair<std::vector<std::pair<size_t, size_t>>, size_t> Minesweeper::CheckNbr_(size_t y, size_t x) const {
    std::vector<std::pair<size_t, size_t>> result;
    size_t mines_around = 0;
    if (((0 <= x - 1) && (x - 1 < width_)) && ((0 <= y - 1) && (y - 1 < height_))) {
        if ((!board_[y - 1][x - 1].ismine)) {
            result.push_back(std::make_pair(y - 1, x - 1));
        } else {
            ++mines_around;
        }
    }
    if (((0 <= x - 1) && (x - 1 < width_)) && ((0 <= y) && (y < height_))) {
        if (!board_[y][x - 1].ismine) {
            result.push_back(std::make_pair(y, x - 1));
        } else {
            ++mines_around;
        }
    }
    if (((0 <= x - 1) && (x - 1 < width_)) && ((0 <= y + 1) && (y + 1 < height_))) {
        if (!board_[y + 1][x - 1].ismine) {
            result.push_back(std::make_pair(y + 1, x - 1));
        } else {
            ++mines_around;
        }
    }
    if (((0 <= x) && (x < width_)) && ((0 <= y - 1) && (y - 1 < height_))) {
        if (!board_[y - 1][x].ismine) {
            result.push_back(std::make_pair(y - 1, x));
        } else {
            ++mines_around;
        }
    }
    if (((0 <= x) && (x < width_)) && ((0 <= y + 1) && (y + 1 < height_))) {
        if (!board_[y + 1][x].ismine) {
            result.push_back(std::make_pair(y + 1, x));

        } else {
            ++mines_around;
        }
    }
    if (((0 <= x + 1) && (x + 1 < width_)) && ((0 <= y - 1) && (y - 1 < height_))) {
        if (!board_[y - 1][x + 1].ismine) {
            result.push_back(std::make_pair(y - 1, x + 1));
        } else {
            ++mines_around;
        }
    }
    if (((0 <= x + 1) && (x + 1 < width_)) && ((0 <= y) && (y < height_))) {
        if (!board_[y][x + 1].ismine) {
            result.push_back(std::make_pair(y, x + 1));
        } else {
            ++mines_around;
        }
    }
    if (((0 <= x + 1) && (x + 1 < width_)) && ((0 <= y + 1) && (y + 1 < height_))) {
        if (!board_[y + 1][x + 1].ismine) {
            result.push_back(std::make_pair(y + 1, x + 1));
        } else {
            ++mines_around;
        }
    }
    return std::make_pair(result, mines_around);
}

void Minesweeper::OpenCell(const Minesweeper::Cell& cell) {
    if (game_status_ == GameStatus::VICTORY || game_status_ == GameStatus::DEFEAT) {
        return;
    }
    if (game_status_ == GameStatus::NOT_STARTED) {
        game_status_ = GameStatus::IN_PROGRESS;
        time_from_start_ = std::time(nullptr);
    }

    if (board_[cell.y][cell.x].isflag) {
        return;
    }

    if (board_[cell.y][cell.x].ismine) {
        for (size_t i = 0; i < board_.size(); ++i) {
            for (size_t j = 0; j < board_[i].size(); ++j) {
                board_[i][j].isopen = true;
                board_[i][j].isflag = false;
            }
        }
        game_status_ = GameStatus::DEFEAT;
        time_ans_ = std::time(nullptr) - time_from_start_;
    } else {
        std::pair<std::vector<std::pair<size_t, size_t>>, size_t> vtr = CheckNbr_(cell.y, cell.x);
        if (vtr.second > 0) {
            board_[cell.y][cell.x].isopen = true;
            --cells_to_open_;
        } else {
            std::deque<std::pair<size_t, size_t>> dq;
            //            std::set<std::pair<size_t, size_t>> used;
            for (auto i : vtr.first) {
                if (used_.find(i) == used_.end()) {
                    dq.push_back(i);
                    used_.insert(i);
                }
            }
            board_[cell.y][cell.x].isopen = true;
            --cells_to_open_;
            used_.insert(std::make_pair(cell.y, cell.x));
            while (!dq.empty()) {
                if (!board_[dq[0].first][dq[0].second].ismine && !board_[dq[0].first][dq[0].second].isflag) {
                    used_.insert(dq[0]);
                    board_[dq[0].first][dq[0].second].isopen = true;
                    --cells_to_open_;
                    vtr = CheckNbr_(dq[0].first, dq[0].second);
                    if (vtr.second == 0) {
                        for (auto i : vtr.first) {
                            if (used_.find(i) == used_.end()) {
                                dq.push_back(i);
                                used_.insert(i);
                            }
                        }
                    }
                    dq.pop_front();
                } else {
                    used_.insert(dq[0]);
                    dq.pop_front();
                }
            }
        }
    }
    if (cells_to_open_ == 0 && game_status_ == GameStatus::IN_PROGRESS) {
        game_status_ = GameStatus::VICTORY;
        time_ans_ = std::time(nullptr) - time_from_start_;
    }
}

void Minesweeper::MarkCell(const Cell& cell) {
    if (game_status_ == GameStatus::VICTORY || game_status_ == GameStatus::DEFEAT) {
        return;
    }

    if (board_[cell.y][cell.x].isflag) {
        board_[cell.y][cell.x].isflag = false;
    } else {
        board_[cell.y][cell.x].isflag = true;
    }
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return game_status_;
}

time_t Minesweeper::GetGameTime() const {
    return time_ans_;
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    Minesweeper::RenderedField field;
    for (size_t i = 0; i < board_.size(); ++i) {
        std::string str;
        for (size_t j = 0; j < board_[i].size(); ++j) {
            if (!board_[i][j].isopen) {
                if (board_[i][j].isflag) {
                    str += '?';
                } else {
                    str += '-';
                }
            }
            if (board_[i][j].isopen && board_[i][j].ismine) {
                str += '*';
            }
            if (board_[i][j].isopen && !board_[i][j].ismine) {
                auto tmp = Minesweeper::CheckNbr_(i, j).second;
                if (tmp == 0) {
                    str += '.';
                } else {
                    str += std::to_string(tmp);
                }
            }
        }
        field.push_back(str);
        str.clear();
    }
    return field;
}
