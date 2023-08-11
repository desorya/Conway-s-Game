import java.io.IOException;

public class GameOfLife {
    static int length = 16;
    static int width = 9;
    private boolean[][] universe;
    private int flag=0;

    // Initialize universe through constructor
    public GameOfLife() {
        this.universe = new boolean[width][length];
        this.universe[0][1] = true;
        this.universe[1][2] = true;
        this.universe[2][0] = true;
        this.universe[2][1] = true;
        this.universe[2][2] = true;
    }

    public void setFlag(int flag) {
        this.flag = flag;
    }

    public void setUniverse(boolean[][] universe) {
        this.universe = universe;
    }


    private void update() {
        boolean[][] newUniverse = new boolean[width][length];

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < length; j++) {
                // Count live neighbors for each element
                int liveNeighbors = countLiveNeighbors(this.universe, i, j);

                // Apply rules
                if (this.universe[i][j]) {
                    newUniverse[i][j] = liveNeighbors == 2 || liveNeighbors == 3;
                } else {
                    newUniverse[i][j] = liveNeighbors == 3;
                }
            }
        }

        equalityCheck(newUniverse);

        // Update universe
        setUniverse(newUniverse);
    }

    // Function to count live neighbors
    private int countLiveNeighbors(boolean[][] universe, int row, int col) {
        int liveNeighbors = 0;

        // Direction array
        int[] dr = {-1, -1, -1, 0, 0, 1, 1, 1};
        int[] dc = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int i = 0; i < 8; i++) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if (nr >= 0 && nr < universe.length && nc >= 0 && nc < universe[0].length && universe[nr][nc]) {
                liveNeighbors++;
            }
        }

        return liveNeighbors;
    }

    // Check if universe doesn't change anymore
    private void equalityCheck(boolean[][] cache) {
        for (int x = 0; x < cache.length; x++)
            for (int y = 0; y < cache[0].length; y++) {
                if (cache[x][y] ^ this.universe[x][y]) {
                    setFlag(1); // Changed
                }
            }
        setFlag(this.flag==0?2:0); // Setup flag if doesn't change, otherwise reset
    }

    // Function to visualize the universe in the terminal
    private void visualize() throws IOException, InterruptedException {
        cls(); // annotate this line if not using cmd to display
        for (boolean[] row : this.universe) {
            for (boolean cell : row) {
                System.out.print(cell ? " \u25A0" : " \u25A1");
            }
            System.out.println();
        }
    }

    public static void cls() throws IOException, InterruptedException {
        new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
    }


    public static void main(String[] args) throws InterruptedException, IOException {
        GameOfLife demo = new GameOfLife();

        while (demo.flag != 2) {
            demo.visualize();
            demo.update();
            Thread.sleep(1000); // Add a delay between generations
        }
    }
}
