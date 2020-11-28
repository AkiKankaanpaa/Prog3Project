#ifndef GAMESTATISTICS_H
#define GAMESTATISTICS_H

enum difficulty{ITYD, HMP, UV, USE};

class Gamestatistics
{
public:
    Gamestatistics(difficulty chosen_diff);
    ~Gamestatistics();
    void change_points(int change);
    int return_points();

private:
    int current_points_;
    int ran_over_maskwearers_;
    int ran_over_maskrefusers_;
};

#endif // GAMESTATISTICS_H
