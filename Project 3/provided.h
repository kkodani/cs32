#ifndef PROVIDED_INCLUDED
#define PROVIDED_INCLUDED

#include <string>

const int VACANT = -1;
const int RED = 0;
const int BLACK = 1;
const int TIE_GAME = -1;

class ScaffoldImpl;

class Scaffold
{
  public:
    Scaffold(int nColumns, int nRows); 
    ~Scaffold(); 
    Scaffold(const Scaffold& other); 
    Scaffold& operator=(const Scaffold& rhs); 
    int cols() const;
    int rows() const;
    int numberEmpty() const;
    int checker(int c, int r) const; 
    void display() const; 
    bool makeMove(int c, int color); 
    int undoMove(int c); 
  private:
    ScaffoldImpl* m_impl;
};

class Player
{
  public:
    Player(std::string nm) : m_name(nm) {}
    virtual ~Player() {}
    std::string name() const { return m_name; };
    virtual bool isInteractive() const { return false; }
    virtual int chooseMove(const Scaffold& s, int N, int color) = 0;
  private:
    std::string m_name;
};

class HumanPlayerImpl;

class HumanPlayer : public Player
{
  public:
    HumanPlayer(std::string nm);
    virtual ~HumanPlayer();
    virtual bool isInteractive() const { return true; }
    virtual int chooseMove(const Scaffold& s, int N, int color);
  private:
    HumanPlayerImpl* m_impl;
      // We prevent a HumanPlayer object from being copied or assigned by
      // declaring the copy constructor and assignment operator private and
      // not implementing them.
    HumanPlayer(const HumanPlayer& other);
    HumanPlayer& operator=(const HumanPlayer& other);
};

class BadPlayerImpl;

class BadPlayer : public Player
{
  public:
    BadPlayer(std::string nm);
    virtual ~BadPlayer();
    virtual int chooseMove(const Scaffold& s, int N, int color);
  private:
    BadPlayerImpl* m_impl;
      // We prevent a BadPlayer object from being copied or assigned by
      // declaring the copy constructor and assignment operator private and
      // not implementing them.
    BadPlayer(const BadPlayer& other);
    BadPlayer& operator=(const BadPlayer& other);
};

class SmartPlayerImpl;

class SmartPlayer : public Player
{
  public:
    SmartPlayer(std::string nm);
    virtual ~SmartPlayer();
    virtual int chooseMove(const Scaffold& s, int N, int color);
  private:
    SmartPlayerImpl* m_impl;
      // We prevent a SmartPlayer object from being copied or assigned by
      // declaring the copy constructor and assignment operator private and
      // not implementing them.
    SmartPlayer(const SmartPlayer& other);
    SmartPlayer& operator=(const SmartPlayer& other);
};

class GameImpl;

class Game
{
  public:
    Game(const Scaffold& s, int N, Player* red, Player* black); 
    ~Game();
    bool completed(int& winner) const; 
    bool takeTurn(); 
    void play(); 
    int checker(int c, int r) const;
  private:
    GameImpl* m_impl;
      // We prevent a Game object from being copied or assigned by
      // declaring the copy constructor and assignment operator private and
      // not implementing them.
    Game(const Game& other);
    Game& operator=(const Game& other);
};

#endif // PROVIDED_INCLUDED
