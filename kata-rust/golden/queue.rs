use std::cell::RefCell;
use std::rc::Rc;

type Link<T> = Option<Rc<RefCell<Node<T>>>>;

struct Node<T> {
    value: T,
    next: Link<T>,
}

/// Singly linked queue: dequeue from `head`, enqueue at `tail`.
/// The tail node is shared by `tail` and its predecessor's `next`, hence `Rc<RefCell<_>>`.
pub struct Queue<T> {
    head: Link<T>,
    tail: Link<T>,
    len: usize,
}

impl<T> Default for Queue<T> {
    fn default() -> Self {
        Self {
            head: None,
            tail: None,
            len: 0,
        }
    }
}

impl<T: Clone> Queue<T> {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn enqueue(&mut self, item: T) {
        let node = Rc::new(RefCell::new(Node {
            value: item,
            next: None,
        }));
        match self.tail.take() {
            Some(old) => old.borrow_mut().next = Some(Rc::clone(&node)),
            None => self.head = Some(Rc::clone(&node)),
        }
        self.tail = Some(node);
        self.len += 1;
    }

    pub fn deque(&mut self) -> Option<T> {
        let node = self.head.take()?;
        self.head = node.borrow_mut().next.take();
        if self.head.is_none() {
            self.tail = None;
        }
        self.len -= 1;
        match Rc::try_unwrap(node) {
            Ok(cell) => Some(cell.into_inner().value),
            Err(_) => unreachable!("dequeued node has no other owners"),
        }
    }

    pub fn peek(&self) -> Option<T> {
        self.head.as_ref().map(|n| n.borrow().value.clone())
    }

    pub fn len(&self) -> usize {
        self.len
    }

    pub fn is_empty(&self) -> bool {
        self.len() == 0
    }
}

impl<T> Drop for Queue<T> {
    /// Iterative drop to avoid deep recursion through the `next` chain.
    fn drop(&mut self) {
        self.tail = None;
        let mut cur = self.head.take();
        while let Some(node) = cur {
            cur = node.borrow_mut().next.take();
        }
    }
}
