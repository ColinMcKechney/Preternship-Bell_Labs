//X11 Helper functions
#ifndef GRAPHICS_H
#define GRAPHICS_H

/* include the X library headers */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/Graph.h"
#include <cmath>

const int node_max = 30;
const double curve_factor = .5;
const int x_size = 1000;
const int y_size = 600;

//Gets the correct unsigned long for the color triplet [0,255] for each
unsigned long RGB(int r,int g, int b)
{
    return b + (g<<8) + (r<<16);
}


Display* create_window(Window& win, GC& gc)
{ 
	unsigned long black,white;

	Display *dis = XOpenDisplay((char *)0);
   	int screen = DefaultScreen(dis);
	black = BlackPixel(dis,screen),
	white = WhitePixel(dis, screen);
   	win = XCreateSimpleWindow(dis,DefaultRootWindow(dis), 0, 0, x_size, y_size, 5, black, white);
	XSetStandardProperties(dis,win,"Graph Visualization Tool","",None,NULL,0,NULL);
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);
    gc=XCreateGC(dis, win, 0,0);        
	XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);
	XClearWindow(dis, win);
	XMapRaised(dis, win);
	return dis;
}

void close_window(Display *dis, Window& win, GC& gc) {
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);					
}

void hold_window(Display *dis, Window& win)
{
	XEvent event;
	KeySym key;
	char text[255];

	while(1)
	{
		XNextEvent(dis, &event);
		if (event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1)
		{
			if (text[0] == 'q') {
				XClearWindow(dis, win);
				return;
			}
		}
	}
}

void draw_graph(Display *dis, Window win, GC gc, Graph graph)
{
	//Initialize nodes in a square matrix
	int per_row = (int)ceil(sqrt((double)graph.vertexCount));
	int v_placed = 0;
	int y = 1;
	int x_scale = x_size / (per_row + 1);
	int y_scale = y_size / (per_row + 1);
	const unsigned int rect_size = 40;
	int node_placements[node_max][2]; //0 is x, 1 is y, assume less than node_max nodes (constant initializers)
	
	char text[255];
	while(v_placed < graph.vertexCount)
	{
		for(int x = 1; x < per_row + 1; x++)
		{
			sprintf(text, "N%d", v_placed + 1);
			//Draw node
			XSetForeground(dis, gc, RGB(210,210,210));
			XFillArc(dis, win, gc, x * x_scale - rect_size, y * y_scale - rect_size, rect_size, rect_size, 0, 360 * 64);
			std::cout<<"Placing at "<<x * x_scale - rect_size<<", "<<y * y_scale - rect_size<<std::endl;
			
			//Draw id text
			XSetForeground(dis, gc, 0);
			XDrawString(dis, win, gc, x * x_scale - rect_size / 2, y * y_scale - rect_size / 2, text, (int) strlen(text));
			node_placements[v_placed][0] = x;
			node_placements[v_placed][1] = y;
			v_placed++;
			if(v_placed >= graph.vertexCount)
			{
				break;
			}
		}
		y++;
	}
	//Draw edges
	int v1x, v1y, v2x, v2y;
	
	std::unordered_map<double, int> slope_map;
	std::unordered_map<int, int> prevent_double_map;
	for(Node n : graph.verticies)
	{
		for(Edge e : n.node_edges)
		{
			//--------------------------------------------For testing, must be resolved! (Could already be resolved in new version)
			//Since I add edges as double sided, the graph is very messy, this takes out every other edge
			if(prevent_double_map.count(e.beginning->node_id) > 0 && prevent_double_map.at(e.beginning->node_id) == e.destination->node_id) { continue; }
			else { prevent_double_map.insert({e.destination->node_id, e.beginning->node_id}); }
			//--------------------------------------------For testing, must be resolved!
			
			//Get v1
			v1x = node_placements[e.beginning->node_id][0] * x_scale - rect_size /2;
			v1y = node_placements[e.beginning->node_id][1] * y_scale - rect_size /2;
			//Get v2
			v2x = node_placements[e.destination->node_id][0] * x_scale - rect_size /2;
			v2y = node_placements[e.destination->node_id][1] * y_scale - rect_size /2;
			std::cout<<"Drawing edge from node "<<e.beginning->node_id<<" to node "<<e.destination->node_id<<std::endl;
			double slope = (v2x - v1x != 0) ? (double)(v2y - v1y) / (double)(v2x - v1x) : 999.0; //Assumes that there won't be a line with 999 slope, would require 999^2 nodes (a lot)
			if(slope_map.count(slope) > 0) //There already is a line with this slope
			{
				//XDraw was depreciated back in the late 1980s apparently... have to use this method
				//Essentially creates a circle with an origin very far away and draws an arc length that corresponds to the two points in question
				//Might move to seperate function in graphics.h to clean up main
				double dx = v2x - v1x;
				double dy = v2y - v1y;
				std::cout<<"COUNT IS "<<slope_map.at(slope)<<std::endl;
				double curve = (slope_map.at(slope) % 2 == 0 ? 1 : -1) * (4 - curve_factor * (slope_map.at(slope) / 2));
				double originx = (v1x + v2x)/2 - dy * curve;
				double originy = (v1y + v2y)/2 + dx * curve;
				double rad = sqrt(pow(v1x - originx, 2) + pow(v1y - originy, 2));
				//Must get the first point on the unit circle going cw
				double angle1 = (acos((originx - v1x) / rad)) * ((originy < v1y) ? 1 : -1) + M_PI;//((originy < v1y) ? 1 : -1);
				///if(angle1 < 0) angle1 += 1 * M_PI;
				double angle2 = (acos((originx - v2x) / rad)) * ((originy < v2y) ? 1 : -1) + M_PI;//((originy < v2y) ? 1 : -1);
				//if(angle2 < 0) angle2 += 1 * M_PI;
				double start_angle = (angle1 < angle2 ? angle1 : angle2) * (180 * 64 / M_PI);
				double slice = ((angle1 > angle2 ? angle1 : angle2) - (angle1 < angle2 ? angle1 : angle2)) * (180 * 64 / M_PI); //Total angle of the slice
				XSetForeground(dis, gc, RGB(255 - (255 /(slope_map.at(slope) + 1)), 0, 0 ) );
				XDrawArc(dis, win, gc, (int)(originx - rad), (int)(originy - rad), (int)rad*2, (int)rad*2, (int)start_angle, (int)slice);
				std::cout<<"Drawing circle: ("<<originx<<", "<<originy<<") r = "<<rad<<" between angle "<<start_angle / 64<<" and "<<(start_angle + slice) / 64<<std::endl;
				std::cout<<"Points should be: ("<<v1x<<", "<<v1y<<") and ("<<v2x<<", "<<v2y<<")\n";
				std::cout<<"Points got: ("<<originx + cos(start_angle / (64 * 180 / M_PI)) * rad<<", "<<originy - sin(start_angle / (64 * 180 / M_PI)) * rad<<") and ("<<originx + cos((start_angle + slice) / (64 * 180 / M_PI)) * rad<<", "<<originy - sin((start_angle + slice) / (64 * 180 / M_PI)) * rad<<")\n";
				slope_map.at(slope)++;
			} else //Straight line much easier, make entry in map
			{
				XSetForeground(dis, gc, 0);
				XDrawLine(dis, win, gc, v1x, v1y, v2x, v2y);
				slope_map.insert({slope, 1});
			}
			//Change to check if curved is needed or not before doing this?
		}
	}
}


#endif