#include "ft_malcolm.h"

int is_hostname(const char *str)
{
	struct in_addr	addr;

	if (!str)
		return 0;
	/* If the string is a pure decimal number (e.g. 3232235777) -> not a hostname */
	if (is_decimal_format(str))
		return 0;
	{
		int has_dot = 0;
		int only_digits_and_dots = 1;
		for (int i = 0; str[i]; i++) {
			if (str[i] == '.') has_dot = 1;
			else if (!ft_isdigit(str[i])) {
				only_digits_and_dots = 0;
				break;
			}
		}
		if (has_dot && only_digits_and_dots)
			return 0;
	}
	/* If it's a valid IPv4 textual representation -> not a hostname */
	if (inet_pton(AF_INET, str, &addr) == 1)
		return (0);
	/* Otherwise it's a hostname */
	return (1);
}

char *resolve_hostname(const char *hostname)
{
	struct addrinfo		hints;		// contiene información de la resolución
	struct addrinfo		*result;
	struct sockaddr_in	*addr_in;	// Contiene la IP resuelta
	char				*ip_str;
	int					status;

	// configurar hints para pedir solo IPv4
	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;		
	hints.ai_socktype = SOCK_STREAM;
	// resolver el nombre
	status = getaddrinfo(hostname, NULL, &hints, &result);
	if (status != 0)
	{
		ft_printf("ft_malcolm: cannot resolve '%s': '%s\n'", hostname, gai_strerror(status));
		return NULL;
	}
	// Extrae la IP
	addr_in = (struct sockaddr_in *)result->ai_addr;
	// Convierte la IP a string
	ip_str = ft_strdup(inet_ntoa(addr_in->sin_addr));
	freeaddrinfo(result);
	return ip_str;
}

void process_hostname_args(t_args *args)
{
	char	*resolved_ip;

	if (is_hostname(args->source_ip))
	{

		resolved_ip = resolve_hostname(args->source_ip);
		if (!resolved_ip)
			exit(EXIT_FAILURE);
		ft_printf("Resolved '%s' to %s\n", args->source_ip, resolved_ip);
		args->source_ip = resolved_ip;
	}
	if (is_hostname(args->target_ip))
	{
		resolved_ip = resolve_hostname(args->target_ip);
		if (!resolved_ip)
			exit(EXIT_FAILURE);
		ft_printf("Resolved '%s' to %s\n", args->target_ip, resolved_ip);
		args->target_ip = resolved_ip;
	}
}
