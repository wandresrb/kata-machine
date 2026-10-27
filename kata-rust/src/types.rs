//! Shared types used by the katas and their tests (port of `src/global.d.ts`).

/// A 2D grid coordinate (`x` = column, `y` = row).
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub struct Point {
    pub x: i32,
    pub y: i32,
}

impl Point {
    pub const fn new(x: i32, y: i32) -> Self {
        Self { x, y }
    }
}

/// A binary tree node that owns its children.
#[derive(Debug, Clone)]
pub struct BinaryNode<T> {
    pub value: T,
    pub left: Option<Box<BinaryNode<T>>>,
    pub right: Option<Box<BinaryNode<T>>>,
}

impl<T> BinaryNode<T> {
    /// Builds a node from an optional left and right subtree.
    pub fn new(value: T, left: Option<BinaryNode<T>>, right: Option<BinaryNode<T>>) -> Self {
        Self {
            value,
            left: left.map(Box::new),
            right: right.map(Box::new),
        }
    }

    /// Builds a node with no children.
    pub fn leaf(value: T) -> Self {
        Self::new(value, None, None)
    }
}

/// A directed, weighted edge to node `to`.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct GraphEdge {
    pub to: usize,
    pub weight: u32,
}

/// `list[node]` holds every edge leaving `node`.
pub type WeightedAdjacencyList = Vec<Vec<GraphEdge>>;

/// `matrix[from][to]` is the edge weight; `0` means "no edge".
pub type WeightedAdjacencyMatrix = Vec<Vec<u32>>;

/// The list interface shared by `ArrayList`, `SinglyLinkedList` and `DoublyLinkedList`.
pub trait List<T> {
    /// Number of items in the list.
    fn len(&self) -> usize;

    fn is_empty(&self) -> bool {
        self.len() == 0
    }

    /// Inserts `item` at the front.
    fn prepend(&mut self, item: T);

    /// Inserts `item` at the back.
    fn append(&mut self, item: T);

    /// Inserts `item` so that it ends up at position `idx`. Panics if `idx > len`.
    fn insert_at(&mut self, item: T, idx: usize);

    /// Removes the first item equal to `item`, returning it (`None` if absent).
    fn remove(&mut self, item: &T) -> Option<T>;

    /// Returns a copy of the item at `idx` (`None` if out of bounds).
    fn get(&self, idx: usize) -> Option<T>;

    /// Removes and returns the item at `idx` (`None` if out of bounds).
    fn remove_at(&mut self, idx: usize) -> Option<T>;
}
