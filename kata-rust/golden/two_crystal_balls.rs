pub fn two_crystal_balls(breaks: &[bool]) -> Option<usize> {
    let step = breaks.len().isqrt().max(1);

    // First ball: jump by sqrt(n) until it breaks.
    let mut i = step;
    while i < breaks.len() && !breaks[i] {
        i += step;
    }

    // Second ball: walk linearly through the last safe block.
    let start = i.saturating_sub(step);
    (start..breaks.len().min(i + 1)).find(|&j| breaks[j])
}
