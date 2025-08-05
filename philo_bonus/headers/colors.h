/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:15:57 by zbengued          #+#    #+#             */
/*   Updated: 2025/08/04 16:11:41 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// Reset
# define COLOR_RESET      "\001\033[0m\002"

// Styles
# define COLOR_BOLD       "\001\033[1m\002"
# define COLOR_UNDERLINE  "\001\033[4m\002"

// (texte)
# define COLOR_BLACK      "\001\033[0;30m\002"
# define COLOR_RED        "\001\033[0;31m\002"
# define COLOR_GREEN      "\001\033[0;32m\002"
# define COLOR_YELLOW     "\001\033[0;33m\002"
# define COLOR_BLUE       "\001\033[0;34m\002"
# define COLOR_MAGENTA    "\001\033[0;35m\002"
# define COLOR_CYAN       "\001\033[0;36m\002"
# define COLOR_WHITE      "\001\033[0;37m\002"

// (bright)
# define COLOR_BRIGHT_BLACK   "\001\033[1;30m\002"
# define COLOR_BRIGHT_RED     "\001\033[1;31m\002"
# define COLOR_BRIGHT_GREEN   "\001\033[1;32m\002"
# define COLOR_BRIGHT_YELLOW  "\001\033[1;33m\002"
# define COLOR_BRIGHT_BLUE    "\001\033[1;34m\002"
# define COLOR_BRIGHT_MAGENTA "\001\033[1;35m\002"
# define COLOR_BRIGHT_CYAN    "\001\033[1;36m\002"
# define COLOR_BRIGHT_WHITE   "\001\033[1;37m\002"

#endif /* COLORS_H */
