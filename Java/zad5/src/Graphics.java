import java.util.HashSet;
import java.util.Objects;
import java.util.Set;
import java.util.Stack;

public class Graphics implements GraphicsInterface {
    CanvasInterface canv;

    public void fillWithColor(Position startingPosition, Color color) throws WrongStartingPosition, NoCanvasException {
        Stack<Position> stck = new Stack<>();
        Set<Position> checked = new HashSet<>();
        Position curpos = startingPosition;
        boolean loop = true;

        if (canv == null) {
            throw new GraphicsInterface.NoCanvasException();
        }

        try {
            canv.setColor(curpos, color);
            stck.add(newpos(curpos, -1, 0));
            stck.add(newpos(curpos, 0, -1));
            stck.add(newpos(curpos, 1, 0));
            stck.add(newpos(curpos, 0, 1));
        } catch (CanvasInterface.CanvasBorderException c) {
            throw new GraphicsInterface.WrongStartingPosition();
        } catch (CanvasInterface.BorderColorException c) {
            try {
                canv.setColor(curpos, c.previousColor);
            } finally {
                throw new GraphicsInterface.WrongStartingPosition();
            }
        }
        checked.add(curpos);
        curpos = stck.pop();

        while (loop) {
            try {
                canv.setColor(curpos, color);

                if (!checked.contains(newpos(curpos, -1, 0)) && !stck.contains(newpos(curpos, -1, 0))) {
                    stck.add(newpos(curpos, -1, 0));
                }
                if (!checked.contains(newpos(curpos, 0, -1)) && !stck.contains(newpos(curpos, 0, -1))) {
                    stck.add(newpos(curpos, 0, -1));
                }
                if (!checked.contains(newpos(curpos, 1, 0)) && !stck.contains(newpos(curpos, 1, 0))) {
                    stck.add(newpos(curpos, 1, 0));
                }
                if (!checked.contains(newpos(curpos, 0, 1)) && !stck.contains(newpos(curpos, 0, 1))) {
                    stck.add(newpos(curpos, 0, 1));
                }

            } catch (CanvasInterface.CanvasBorderException ignored) {
            } catch (CanvasInterface.BorderColorException c) {
                try {
                    canv.setColor(curpos, c.previousColor);
                } catch (CanvasInterface.CanvasBorderException | CanvasInterface.BorderColorException ignored) {
                }
            } finally {
                checked.add(curpos);
                if (stck.isEmpty()) {
                    loop = false;
                }
                if (loop) {
                    curpos = stck.pop();
                }
            }
        }
    }

    public void setCanvas(CanvasInterface canvas) {
        canv = canvas;
    }

    Position newpos(Position pos, int col, int row) {
        return new Position2D(pos.getCol() + col, pos.getRow() + row);
    }

    static class Position2D implements Position {

        private final int col;
        private final int row;

        public Position2D(int col, int row) {
            this.col = col;
            this.row = row;
        }

        @Override
        public int getRow() {
            return row;
        }

        @Override
        public int getCol() {
            return col;
        }

        @Override
        public String toString() {
            return "Position2D [col=" + col + ", row=" + row + "]";
        }

        @Override
        public int hashCode() {
            return Objects.hash(col, row);
        }

        @Override
        public boolean equals(Object obj) {
            if (this == obj)
                return true;
            if (obj == null)
                return false;
            if (getClass() != obj.getClass())
                return false;
            Position2D other = (Position2D) obj;
            return col == other.col && row == other.row;
        }
    }
}


