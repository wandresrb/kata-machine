use std::cell::RefCell;
use std::rc::{Rc, Weak};

use crate::types::List;

// Strong pointers go forward (head -> tail), weak pointers go backward,
// so there are no reference cycles and dropping the list frees every node.
type Link<T> = Option<Rc<RefCell<Node<T>>>>;

struct Node<T> {
    value: T,
    next: Link<T>,
    prev: Option<Weak<RefCell<Node<T>>>>,
}

pub struct DoublyLinkedList<T> {
    head: Link<T>,
    tail: Link<T>,
    len: usize,
}

impl<T> Default for DoublyLinkedList<T> {
    fn default() -> Self {
        Self {
            head: None,
            tail: None,
            len: 0,
        }
    }
}

impl<T> DoublyLinkedList<T> {
    pub fn new() -> Self {
        Self::default()
    }

    fn node_at(&self, idx: usize) -> Link<T> {
        if idx >= self.len {
            return None;
        }
        let mut cur = self.head.clone();
        for _ in 0..idx {
            cur = cur?.borrow().next.clone();
        }
        cur
    }

    /// Unlinks `node` from the list and returns its value.
    fn unlink(&mut self, node: Rc<RefCell<Node<T>>>) -> T {
        let next = node.borrow_mut().next.take();
        let prev = node.borrow_mut().prev.take().and_then(|w| w.upgrade());

        match &next {
            Some(n) => n.borrow_mut().prev = prev.as_ref().map(Rc::downgrade),
            None => self.tail = prev.clone(),
        }
        match &prev {
            Some(p) => p.borrow_mut().next = next,
            None => self.head = next,
        }
        self.len -= 1;

        match Rc::try_unwrap(node) {
            Ok(cell) => cell.into_inner().value,
            Err(_) => unreachable!("unlinked node must have no other strong refs"),
        }
    }
}

impl<T: Clone + PartialEq> List<T> for DoublyLinkedList<T> {
    fn len(&self) -> usize {
        self.len
    }

    fn prepend(&mut self, item: T) {
        let node = Rc::new(RefCell::new(Node {
            value: item,
            next: None,
            prev: None,
        }));
        match self.head.take() {
            Some(old) => {
                old.borrow_mut().prev = Some(Rc::downgrade(&node));
                node.borrow_mut().next = Some(old);
            }
            None => self.tail = Some(Rc::clone(&node)),
        }
        self.head = Some(node);
        self.len += 1;
    }

    fn append(&mut self, item: T) {
        let node = Rc::new(RefCell::new(Node {
            value: item,
            next: None,
            prev: None,
        }));
        match self.tail.take() {
            Some(old) => {
                node.borrow_mut().prev = Some(Rc::downgrade(&old));
                old.borrow_mut().next = Some(Rc::clone(&node));
            }
            None => self.head = Some(Rc::clone(&node)),
        }
        self.tail = Some(node);
        self.len += 1;
    }

    fn insert_at(&mut self, item: T, idx: usize) {
        assert!(
            idx <= self.len,
            "insert_at index {idx} out of bounds (len {})",
            self.len
        );
        if idx == 0 {
            return self.prepend(item);
        }
        if idx == self.len {
            return self.append(item);
        }
        let next = self.node_at(idx).expect("0 < idx < len");
        let prev = next
            .borrow()
            .prev
            .as_ref()
            .and_then(Weak::upgrade)
            .expect("idx > 0");
        let node = Rc::new(RefCell::new(Node {
            value: item,
            next: Some(Rc::clone(&next)),
            prev: Some(Rc::downgrade(&prev)),
        }));
        next.borrow_mut().prev = Some(Rc::downgrade(&node));
        prev.borrow_mut().next = Some(node);
        self.len += 1;
    }

    fn remove(&mut self, item: &T) -> Option<T> {
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            if node.borrow().value == *item {
                return Some(self.unlink(node));
            }
            cur = node.borrow().next.clone();
        }
        None
    }

    fn get(&self, idx: usize) -> Option<T> {
        self.node_at(idx).map(|n| n.borrow().value.clone())
    }

    fn remove_at(&mut self, idx: usize) -> Option<T> {
        let node = self.node_at(idx)?;
        Some(self.unlink(node))
    }
}

impl<T> Drop for DoublyLinkedList<T> {
    /// Iterative drop to avoid deep recursion through the `next` chain.
    fn drop(&mut self) {
        self.tail = None;
        let mut cur = self.head.take();
        while let Some(node) = cur {
            cur = node.borrow_mut().next.take();
        }
    }
}
