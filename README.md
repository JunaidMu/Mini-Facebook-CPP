# 📘 Mini Facebook – Console-Based Social Media Simulator

A C++ object-oriented console application that simulates key functionalities of a social media platform like Facebook. Users can make posts, share memories, like and comment on posts, and maintain friend/page connections—all within a file-driven simulation.

---

## 🚀 Features

* 📅 Custom date simulation
* 👤 Users with friend lists
* 📄 Pages that can be liked
* 🧵 Post creation with activity tags (e.g., feeling, thinking about)
* 💬 Like and comment functionality
* 🧠 Memory sharing feature ("On this day" behavior)
* 🏡 Home feed displaying posts from friends and liked pages (posted within last 2 days)
* 📁 File-based input (Users, Pages, Posts, Comments, Activities)

---

## 🧩 File Structure

| File            | Description                           |
| --------------- | ------------------------------------- |
| `Project.cpp`   | Main application logic                |
| `Users.txt`     | Stores all users                      |
| `Pages.txt`     | Stores all pages                      |
| `Liked.txt`     | Links between users and pages/friends |
| `Posts.txt`     | Posts shared by users and pages       |
| `Comments.txt`  | Comments on posts                     |
| `Activites.txt` | Activities associated with posts      |

---

## 📸 Project Snapshots

Below are sample outputs captured from the console while running the simulator:

### 🖼️ SS1: View Friend List and View Liked Pages

Displays the current user's (`u7`) friend list and the pages they like.

![View Friend List and Liked Pages](images/ss1.png)

---

### 🖼️ SS2: Latest Post and View Home

Shows the most recent post and home feed consisting of posts by user, friends, and pages (within 2-day limit).

![Latest Post and Home Feed](images/ss2.png)

---

### 🖼️ SS3: Share a Memory, View Timeline, Post Comment, and View Post

Includes:

* Sharing a memory (e.g., post10)
* Timeline updated with the memory
* Commenting on a post
* Viewing the full post with comments

![Memory, Timeline, and Comment](images/ss3.png)

---

## 📚 Author

**Junaid Muhammad**
FAST-NUCES Lahore
