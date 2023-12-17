#ifndef DAY17_HPP
#define DAY17_HPP

#include <vector>
#include <queue>
#include <map>

#include "../general.hpp"

namespace day17 {
    typedef std::vector<std::vector<int>> gridtype;

    const ll INF = 1000000000000000ll;

    struct distsel {
        cg x;
        Direction dir;

        bool operator<(const distsel& o) const {
            if (x != o.x) return x < o.x;
            return dir < o.dir;
        }
    };

    struct qel {
        cg x;
        Direction dir;
        ll cost;

        bool operator>(const qel &o) const {
            if (cost != o.cost) return cost > o.cost;
            if (x != o.x) return x < o.x;
            return dir < o.dir;
        }

        distsel del() const {
            return {x, dir};
        }
    };

    ll find_path(const gridtype &grid, bool ultra_paths=false) {
        std::priority_queue<qel, std::vector<qel>, std::greater<qel>> pq;
        std::map<distsel, ll> dists;

        pq.push({{0,0}, east, 0});
        pq.push({{0, 0}, south, 0});
        while (!pq.empty()) {
            qel top = pq.top();
            debug("top: %d,%d with dir=%c and cost=%lld\n", top.x.i, top.x.j, top.dir, top.cost);
            pq.pop();
            if (dists.count(top.del()) > 0 && dists[top.del()] < top.cost) continue;

            if (top.x.i == grid.size()-1 && top.x.j == grid[0].size()-1) {
                return top.cost;
            }

            // we can only go in a normal direction
            std::vector<Direction> normals = get_normal(top.dir);
            for (Direction dir : normals) {
                cg curr = top.x;
                ll d = dists[top.del()];
                for (int i = 0; i < (ultra_paths ? 10 : 3); i++) {
                    if (!curr.can_follow(dir, grid.size(), grid[0].size()))
                        break;
                    curr = curr.follow(dir);
                    d += grid AT(curr);

                    distsel nov{curr, dir};
                    if (dists.count(nov) > 0 && dists[nov] <= d) continue;
                    if (!ultra_paths || i >= 3) {
                        dists[nov] = d;
                        pq.push({curr, dir, d});
                    }
                }
            }
        }
        return INF;
    }
}

#endif
