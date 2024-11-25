#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"
#include "model.hpp"

#define TILE_SIZE 0.128f

struct Coord{
  int X, Y;
};

struct Piece{
    char type; //k = Rei, q = Dama, b = Bispo, n = Cavalo, r = Torre, p = Peão
    int color;

    glm::vec3 pos;
    int X, Y;

    bool captured = false;
    bool hasMoved = false;
};

struct Tile{
  int X;
  int Y;
  int color;

  bool exists = false;
  int pieceID = -1;

  glm::vec3 pos;
};

class Window : public abcg::OpenGLWindow {
protected:
  void onEvent(SDL_Event const &event) override;
  void onCreate() override;
  void onUpdate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;

private:
  glm::ivec2 m_viewportSize{};

  Model m_tile;
  Model m_pawn;
  Model m_rook;
  Model m_knight;
  Model m_bishop;
  Model m_queen;
  Model m_king;

  Tile board[8][8];
  std::vector<Piece> pieces;
  Coord whiteKing, blackKing;

  int turn = 0;

  int selectedX = 0;
  int selectedY = 0;
  bool movingPiece = false;
  int movingPieceID = -1;

  Coord lastStart = {-1,-1};
  Coord lastEnd = {-1,-1};

  std::vector<Coord> legalMoves;

  float m_zoom = 45.0f;

  glm::mat4 m_modelMatrix{1.0f};
  glm::mat4 m_viewMatrix{1.0f};
  glm::mat4 m_projMatrix{1.0f};
  bool rotating = false;
  float rotationAngle = 0;

  GLuint m_program{};

  std::vector<Piece> setupBoard();

  bool isLegal(Coord target);
  std::vector<Coord> getLegalMoves(Piece p);
  bool isThreatened(Coord target, int color);

  void renderModel(Model m, int color, glm::vec3 pos);
  void renderBoard();
  void renderPieces();
};

#endif