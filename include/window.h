/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 19:17:00 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/04 18:07:00 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "GLFW/glfw3.h"
# include "ft_printf.h"
# include "ft_color.h"

/*
** Callback called when a key state changes
**
** @callback t_f_window_callback_key
** @param user_ptr - the unmodified pointer which was given
** to window_callback_loop() or window_loop()
** @param key - the key code of the event's key, as defined in glfw
** @param action - the action performed for the given @a key, as defined in glfw
*/
typedef void		(*t_f_window_callback_key)(void *user_ptr,
		int key, int action);

/*
** Callback called when the mouse is moving
**
** @callback t_f_window_callback_mouse_motion
** @param user_ptr - the unmodified pointer which was given
** to window_callback_loop() or window_loop()
** @param pos_x - the screen x position the mouse was moved to
** @param pos_y - the screen y position the mouse was moved to
*/
typedef void		(*t_f_window_callback_mouse_motion)(void *user_ptr,
		double pos_x, double pos_y);

/*
** Callback called when a mouse button state changes
**
** @callback t_f_window_callback_mouse_button
** @param user_ptr - the unmodified pointer which was given
** to window_callback_loop() or window_loop()
** @param button - the button code of the event's key, as defined in glfw
** @param action - the action performed for the given @abutton,
** as defined in glfw
*/
typedef void		(*t_f_window_callback_mouse_button)(void *user_ptr,
		int button, int action);

/*
** Callback called when the mouse wheel is scrolled
**
** @callback t_f_window_callback_mouse_scroll
** @param user_ptr - the unmodified pointer which was given
** to window_callback_loop() or window_loop()
** @param scroll_x - the scroll x offset value of the mouse wheel
** @param scroll_y - the scroll y offset value of the mouse wheel
*/
typedef void		(*t_f_window_callback_mouse_scroll)(void *user_ptr,
		double scroll_x, double scroll_y);

/*
** Callback called in a loop if window_callback_loop() is used
**
** @callback t_f_window_callback_loop
** @param user_ptr - the unmodified pointer which was given
** @param elapsed - elapsed time since last call ( in milliseconds )
** to window_callback_loop()
*/
typedef void		(*t_f_window_callback_loop)(void *user_ptr, double elapsed);

/*
** Window object, must be initialized by window_create()
**
** @var glfw_win - the GLFWwindow pointer used internally
** @var user_ptr - the unmodified pointer which was given
** to window_callback_loop() or window_loop()
** @var width - the window width
** @var height - the window height
** @var should_close - TRUE if the window should close before next loop,
** FALSE otherwise
** @var f_callback_key - callback called when a key state changes
** @var f_callback_key - callback called when the mouse is moving
** @var f_callback_key - callback called when a mouse button state changes
** @var f_callback_key - callback called when the mouse wheel is scrolled
*/
typedef struct		s_window
{
	GLFWwindow							*glfw_win;
	void								*user_ptr;
	int									width;
	int									height;
	int									should_close;
	t_f_window_callback_key				f_callback_key;
	t_f_window_callback_mouse_motion	f_callback_mouse_motion;
	t_f_window_callback_mouse_button	f_callback_mouse_button;
	t_f_window_callback_mouse_scroll	f_callback_mouse_scroll;
}					t_window;

/*
** Creates a window and opens it
**
** @param[out] win - the #t_window object to initialize
** @param width - the width of the window viewport
** @param height - the height of the window viewport
** @param title - the title of the window
** @return - FALSE if window creation failed, TRUE otherwise
*/
int					window_create(t_window *win, unsigned int width,
		unsigned int height, char *title);

/*
** Destroys a window
**
** @param win - the concerned #t_window object
*/
void				window_destroy(t_window *win);

/*
** Clears the whole window viewport
**
** @param win - the concerned #t_window object
** @param color - the clear color
*/
void				window_clear(t_window *win, t_clrf_rgb color);

/*
** Swaps render buffers
**
** Should be used when you want stuff to appear to the screen
** @param win - the concerned #t_window object
*/
void				window_swap_buffers(t_window *win);

/*
** Sets the keyboard event callback for @a win
**
** @param win - the concerned #t_window object
** @param {t_f_window_callback_key} f_callback - the callback,
** or NULL if it needs to be disabled
*/
void				window_callback_key(t_window *win,
		t_f_window_callback_key f_callback);

/*
** Sets the mouse motion event callback for @a win
**
** @param win - the concerned #t_window object
** @param {t_f_window_callback_mouse_motion} f_callback - the callback,
** or NULL if it needs to be disabled
*/
void				window_callback_mouse_motion(t_window *win,
		t_f_window_callback_mouse_motion f_callback);

/*
** Sets the mouse button event callback for @a win
**
** @param win - the concerned #t_window object
** @param {t_f_window_callback_mouse_button} f_callback - the callback,
** or NULL if it needs to be disabled
*/
void				window_callback_mouse_button(t_window *win,
		t_f_window_callback_mouse_button f_callback);

/*
** Sets the mouse scroll event callback for @a win
**
** @param win - the concerned #t_window object
** @param {t_f_window_callback_mouse_scroll} f_callback - the callback,
** or NULL if it needs to be disabled
*/
void				window_callback_mouse_scroll(t_window *win,
		t_f_window_callback_mouse_scroll f_callback);

/*
** Sets the loop event callback for @a win and loops till the window is closed
**
** If @a f_loop is set, loops @a f_loop till the window is closed,
** if it is NULL, only events are fired whenever they occur
** @param win - the concerned #t_window object
** @param {t_f_window_callback_loop} f_loop - the callback,
** or NULL if it needs to be disabled
** @param user_ptr - a pointer that can be set by the user which will be sent
** unmodified to all other callbacks
*/
void				window_callback_loop(t_window *win,
		void (*f_loop)(void*, double), void *user_ptr);

/*
** Loops till the window is closed
**
** Only events are fired whenever they occur
** @param win - the concerned #t_window object
** @param user_ptr - a pointer that can be set by the user which will be sent
** unmodified to all other callbacks
*/
void				window_loop(t_window *win, void *user_ptr);

#endif
