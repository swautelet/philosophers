# philosophers

## Usage (mac only) -- 👈

```bash
git clone https://github.com/swautelet/philosophers.git && cd philosophers/philo && make && ./philosophers 10 450 200 200 10
```

## Topics -- 🗝
- multi-threading
- multi-process 
- C

## Challenge -- 💡

This project is a classic multi-threading problem. There are philosphers around a table each philosopher being a thread they each have a stick but they need two to eat. they have to share the sticks with thei neighbour in order to eat. if they don't eat fast enough theey die. 
Each stick is a mutex and of course any datarace is prohibited. 
