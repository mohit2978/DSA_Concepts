Great question — this is about building a **mental framework**, not memorizing solutions.

---

### The Master Framework for Interval Problems

Every interval problem asks you to do **one of these 5 things**:

```
1. COMBINE    → merge overlapping intervals
2. COUNT      → how many overlap at a point / min rooms needed
3. REMOVE     → minimum removals to eliminate all overlaps
4. INSERT     → add a new interval into existing ones
5. COVER      → cover all points with minimum intervals
```

Once you identify **which bucket** the problem falls into, the approach follows automatically.

---

### The Decision Tree

```
Read the problem
      │
      ▼
What is the goal?
      │
      ├─→ "merge / combine overlaps"          → Sort by START
      │                                          sweep + expand
      │
      ├─→ "max overlap at any point"           → Sort by START
      │   "min rooms / platforms needed"         use min-heap or +1/-1 sweep
      │
      ├─→ "min removals to make non-overlap"   → Sort by END
      │   "max intervals you can KEEP"           greedy activity selection
      │
      ├─→ "insert new interval"                → Find position, merge neighbors
      │
      └─→ "cover all points / min arrows"      → Sort by END
                                                 greedy cover
```

---

### The 3 Questions to Ask Immediately

When you see an interval problem, ask these in order:

```
Q1: Am I combining things  OR  selecting things?
        ↓                          ↓
    sort by START             sort by END

Q2: Do I need a count  OR  a yes/no  OR  a list?
        ↓                    ↓               ↓
    heap/sweep            greedy          simulate

Q3: Can intervals be reused OR used once only?
        ↓                          ↓
    unbounded                  greedy pick once
```

---

### Pattern → Approach Table

| What problem says | Immediately think |
|---|---|
| "merge overlapping" | sort start, sweep right |
| "minimum rooms / platforms" | sort start, min-heap of end times |
| "maximum overlap count" | events: +1 at start, -1 at end, sweep |
| "minimum removals" | sort end, greedy keep earliest finish |
| "insert interval" | binary search position, merge with neighbors |
| "minimum arrows to burst balloons" | sort end, greedy shoot at earliest end |
| "meeting schedule — can attend all" | sort start, check no overlap |
| "find free time slots" | merge all, find gaps |

---

### The Two Sort Keys — When and Why

This is the **single most important** thing to internalize:

```
Sort by START when...          Sort by END when...
─────────────────────          ───────────────────
you care about WHERE           you care about HOW MUCH
something begins               future space is blocked

goal = detect/merge overlap    goal = maximize what you keep

overlap check needs            greedy needs earliest
left boundary first            finish first

"what's already open           "what frees up
 when this starts?"             room fastest?"
```

---

### How to Spot the Trick Instantly

Train yourself to read these **signal words**:

```
"merge"            → sort START, expand window
"non-overlapping"  → sort END, greedy
"minimum remove"   → sort END, greedy (same as above)
"maximum keep"     → sort END, greedy (same again)
"minimum rooms"    → sort START, heap
"can attend all"   → sort START, check gaps
"cover range"      → sort START or END depending on variant
```

---

### The 5 Problem Types with One-Line Solutions

**Type 1 — Merge Overlapping** `[[1,3],[2,6]] → [[1,6]]`
```
sort by start → if next.start <= last.end → expand end
```

**Type 2 — Minimum Rooms** `"how many meetings overlap at peak?"`
```
sort by start → min-heap of end times → heap size = rooms needed
```

**Type 3 — Minimum Removals** `"fewest removals for no overlap"`
```
sort by end → greedily keep earliest-ending → answer = total - kept
```

**Type 4 — Insert Interval** `"insert [2,5] into [[1,3],[6,9]]"`
```
find overlap range → merge all touching intervals → reconstruct
```

**Type 5 — Minimum Arrows** `"burst all balloons with fewest arrows"`
```
sort by end → shoot at earliest end → counts intervals one arrow kills
```

---

### The Mental Model That Ties It All Together

```
Every interval has two edges:

LEFT edge (start)                RIGHT edge (end)
─────────────────                ────────────────
"when does it enter?"            "when does it leave?"
"does it conflict                "how long does it
 with what's open?"               occupy space?"

Sort by LEFT  →  process in        Sort by RIGHT →  process in
                 arrival order                       departure order

Use when:                          Use when:
detecting collisions               maximizing future availability
merging groups                     greedy selection
```

Think of it like a **airport gate**:

```
Sort by ARRIVAL   → who gets gate first? (merge/detect conflicts)
Sort by DEPARTURE → who frees gate soonest? (maximize usage)
```

---

### Practicing This Framework

When you see a new interval problem, do this before coding:

```
Step 1: Identify the TYPE (combine / count / remove / insert / cover)
Step 2: Ask "do I care about LEFT edge or RIGHT edge?"
Step 3: Pick sort key (start or end)
Step 4: Ask "do I need exact state (heap) or just a count (greedy)?"
Step 5: Write the sweep loop
```

After 10 problems this becomes automatic — you'll know the sort key within 30 seconds of reading the problem. The framework is small enough to internalize completely:

```
┌─────────────────────────────────────────┐
│  Interval problem?                      │
│                                         │
│  Merge/detect overlap  →  sort START   │
│  Maximize keep/minimize remove → sort END│
│  Count simultaneous    →  sort START   │
│                           + heap/sweep  │
└─────────────────────────────────────────┘
```

That's the entire mental model. Everything else is just implementation details.