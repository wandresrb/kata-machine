use crate::types::Point;

const DIRS: [(i32, i32); 4] = [(0, -1), (1, 0), (0, 1), (-1, 0)];

pub fn solve(maze: &[&str], wall: char, start: Point, end: Point) -> Vec<Point> {
    let grid: Vec<Vec<char>> = maze.iter().map(|row| row.chars().collect()).collect();
    let mut seen: Vec<Vec<bool>> = grid.iter().map(|row| vec![false; row.len()]).collect();
    let mut path = Vec::new();
    walk(&grid, wall, start, end, &mut seen, &mut path);
    path
}

fn walk(
    grid: &[Vec<char>],
    wall: char,
    cur: Point,
    end: Point,
    seen: &mut [Vec<bool>],
    path: &mut Vec<Point>,
) -> bool {
    // Off the map?
    let (Ok(x), Ok(y)) = (usize::try_from(cur.x), usize::try_from(cur.y)) else {
        return false;
    };
    let Some(&cell) = grid.get(y).and_then(|row| row.get(x)) else {
        return false;
    };
    if cell == wall || seen[y][x] {
        return false;
    }

    seen[y][x] = true;
    path.push(cur);
    if cur == end {
        return true;
    }
    for (dx, dy) in DIRS {
        if walk(
            grid,
            wall,
            Point::new(cur.x + dx, cur.y + dy),
            end,
            seen,
            path,
        ) {
            return true;
        }
    }
    path.pop();
    false
}
