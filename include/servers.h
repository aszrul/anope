/* Anope */
extern CoreExport Server *Me;

extern CoreExport void CapabParse(int ac, const char **av);

extern CoreExport void do_server(const std::string &source, const std::string &servername, unsigned int hops, const std::string &descript, const std::string &numeric);
extern CoreExport void do_squit(const char *source, int ac, const char **av);

extern CoreExport const char *ts6_uid_retrieve();
extern CoreExport const char *ts6_sid_retrieve();

/* Types of capab
 */
enum CapabType
{
	CAPAB_BEGIN,

	CAPAB_NOQUIT,
	CAPAB_TSMODE,
	CAPAB_UNCONNECT,
	CAPAB_NICKIP,
	CAPAB_NSJOIN,
	CAPAB_ZIP,
	CAPAB_BURST,
	CAPAB_TS3,
	CAPAB_TS5,
	CAPAB_DKEY,
	CAPAB_DOZIP,
	CAPAB_DODKEY,
	CAPAB_QS,
	CAPAB_SCS,
	CAPAB_PT4,
	CAPAB_UID,
	CAPAB_KNOCK,
	CAPAB_CLIENT,
	CAPAB_IPV6,
	CAPAB_SSJ5,
	CAPAB_SN2,
	CAPAB_VHOST,
	CAPAB_TOKEN,
	CAPAB_SSJ3,
	CAPAB_NICK2,
	CAPAB_VL,
	CAPAB_TLKEXT,
	CAPAB_CHANMODE,
	CAPAB_SJB64,
	CAPAB_NICKCHARS,

	CAPAB_END
};

/* CAPAB stuffs */
struct CapabInfo
{
	std::string Token;
	CapabType Flag;
};

extern CoreExport Flags<CapabType> Capab;
extern CoreExport CapabInfo Capab_Info[];

/** Flags set on servers
 */
enum ServerFlag
{
	/* Server is syncing */
	SERVER_SYNCING,
	/* This server was juped */
	SERVER_JUPED
};

/** Class representing a server
 */
class Server : public Flags<ServerFlag>
{
 private:
	/* Server name */
	std::string Name;
	/* Hops between services and server */
	unsigned int Hops;
	/* Server description */
	std::string Description;
	/* Server ID */
	std::string SID;
	/* Links for this server */
	std::list<Server *>* Links;
	/* Uplink for this server */
	Server *UplinkServer;

	/* Reason this server was quit */
	std::string QReason;

 public:
	/** Constructor
	 * @param uplink The uplink this server is from, is only NULL when creating Me
	 * @param name The server name
	 * @param hops Hops from services server
	 * @param description Server rdescription
	 * @param sid Server sid/numeric
	 */
	Server(Server *uplink, const std::string &name, unsigned int hops, const std::string &description, const std::string &sid);

	/** Destructor
	 */
	~Server();

	/** Delete this server with a reason
	 * @param reason The reason
	 */
	void Delete(const std::string &reason);

	/** Get the name for this server
	 * @return The name
	 */
	const std::string& GetName() const;

	/** Get the number of hops this server is from services
	 * @return Number of hops
	 */
	unsigned int GetHops() const;

	/** Set the server description
	 * @param desc The new description
	 */
	void SetDescription(const std::string& desc);

	/** Get the server description
	 * @return The server description
	 */
	const std::string& GetDescription() const;

	/** Get the server numeric/SID
	 * @return The numeric/SID
	 */
	const std::string& GetSID() const;

	/** Get the list of links this server has, or NULL if it has none
	 * @return A list of servers
	 */
	const std::list<Server*>* GetLinks() const;

	/** Get the uplink server for this server, if this is our uplink will be Me
	 * @return The servers uplink
	 */
	Server* GetUplink() const;

	/** Adds a link to this server
	 * @param s The linking server
	 */
	void AddLink(Server *s);

	/** Delinks a server from this server
	 * @param s The server
	 */
	void DelLink(Server *s);

	/** Finish syncing this server and optionally all links to it
	 * @param SyncLinks True to sync the links for this server too (if any)
	 */
	void Sync(bool SyncLinks);

	/** Check if this server is synced
	 * @return true or false
	 */
	bool IsSynced() const;

	/** Check if this server is ULined
	 * @return true or false
	 */
	bool IsULined() const;

	/** Find a server
	 * @param name The name or SID/numeric
	 * @param s The server list to search for this server on, defaults to our Uplink
	 * @return The server
	 */
	static Server* Find(const std::string &name, Server *s = NULL);
};

