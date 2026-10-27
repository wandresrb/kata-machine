use kata::code::maze_solver::solve;
use kata::types::Point;

/// Marks every in-bounds point of `path` with `*` (port of the TS `drawPath`).
fn draw_path(maze: &[&str], path: &[Point]) -> Vec<String> {
    let mut grid: Vec<Vec<char>> = maze.iter().map(|row| row.chars().collect()).collect();
    for p in path {
        let (Ok(x), Ok(y)) = (usize::try_from(p.x), usize::try_from(p.y)) else {
            continue;
        };
        if let Some(cell) = grid.get_mut(y).and_then(|row| row.get_mut(x)) {
            *cell = '*';
        }
    }
    grid.into_iter().map(String::from_iter).collect()
}

#[test]
fn maze_solver() {
    let maze = [
        "xxxxxxxxxx x",
        "x        x x",
        "x        x x",
        "x xxxxxxxx x",
        "x          x",
        "x xxxxxxxxxx",
    ];

    let maze_result = [
        Point::new(10, 0),
        Point::new(10, 1),
        Point::new(10, 2),
        Point::new(10, 3),
        Point::new(10, 4),
        Point::new(9, 4),
        Point::new(8, 4),
        Point::new(7, 4),
        Point::new(6, 4),
        Point::new(5, 4),
        Point::new(4, 4),
        Point::new(3, 4),
        Point::new(2, 4),
        Point::new(1, 4),
        Point::new(1, 5),
    ];

    // there is only one path through
    let result = solve(&maze, 'x', Point::new(10, 0), Point::new(1, 5));
    assert_eq!(draw_path(&maze, &result), draw_path(&maze, &maze_result));
}
