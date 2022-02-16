/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlahmaid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 02:52:16 by rlahmaid          #+#    #+#             */
/*   Updated: 2022/02/16 02:52:23 by rlahmaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main()
{
	execve(NULL, NULL, NULL);
	printf("%s\n", strerror(errno));
}
