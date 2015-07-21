#ifndef ARGO_LOADER_H_
#define ARGO_LOADER_H_

#include <stdint.h>
#include <wchar.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include <set>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Argo {
	class Universe;
	class Torrent;

#ifdef _WIN32
#define CALLCONV __stdcall
#else
#define CALLCONV
#endif

	class ITorrentEventObserver;
    class SHA1Hash;
	struct UniverseObserverCallbackSet;

    //public static void RemoveTorrent(IntPtr _ucontainer, [In, MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.I1, SizeConst = 20)]byte[]infoHash)
    typedef void(CALLCONV *REMOVE_TORRENT_PROC)(void*, const char*);
    //public static void SetExternalIP(IntPtr _ucontainer, [MarshalAs(UnmanagedType.LPWStr)] string val)
    typedef void(CALLCONV *SET_EXTERNAL_IP_PROC)(void*, const char*);

	class SHA1Hash
	{
	public:
		SHA1Hash()
		{
			memset(value, 0, sizeof(value));
		}
		SHA1Hash(const SHA1Hash &other)
		{
			memcpy(value, other.value, sizeof(value));
		}
		SHA1Hash(const char *other)
		{
			memcpy(value, other, sizeof(value));
		}
		
		bool operator < (const SHA1Hash &other) const
		{
			return memcmp(value, other.value, sizeof(value)) < 0;
		}
		
		bool operator == (const SHA1Hash &other) const
		{
		return memcmp(value, other.value, sizeof(value)) == 0;
		}
		
		char value[20];
	};

	// Callback types
	// delegate void MetadataReceivedProc([MarshalAs(UnmanagedType.LPArray, ArraySubType=UnmanagedType.U1)] byte[] hash, IntPtr ctx);
	typedef void (CALLCONV *METADATA_RECEIVED_PROC)(char *, void *);

	// public static int LoadTorrent(IntPtr _ucontainer, [MarshalAs(UnmanagedType.BStr)] string file, ref IntPtr resultPtr)
    typedef int(CALLCONV *LOADTORRENTPROC)(void*, const wchar_t*, void**);
	// public static int LookupTorrent(IntPtr _ucontainer, [MarshalAs(UnmanagedType.LPArray, ArraySubType=UnmanagedType.U1)] byte []hash, IntPtr ctx);
	typedef int(CALLCONV *LOOKUP_TORRENT_PROC)(void *, const char *, void**);
	// public static int LookupMetadata(IntPtr _ucontainer, [MarshalAs(UnmanagedType.LPArray, ArraySubType=UnmanagedType.U1)] byte []hash, IntPtr ctx);
	typedef int(CALLCONV *LOOKUP_METADATA_PROC)(void *, const char *, void **);
    // public static IntPtr CreateUniverse([In, MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.U1, SizeConst = 20)] byte[] peerIdBytes, int localIp, int port)

	class ITorrentEventObserver
	{
	public:
		virtual ~ITorrentEventObserver() { }
		virtual void onMetadataReceived() { }
		virtual void onPieceCompleted(int piece) { }
		virtual void onTorrentCompleted() { }
		virtual void onTorrentReaped() { }
	};

	struct TorrentObserverCallbackSet
	{
		void *context;

		typedef void(CALLCONV*TorrentObserverCompleted)(void *context);
		typedef void(CALLCONV*TorrentObserverPieceCompleted)(void *context, int piece);
		typedef void(CALLCONV*TorrentObserverMetadataReceived)(void *context);

		TorrentObserverCompleted completed;
		TorrentObserverPieceCompleted pieceCompleted;
		TorrentObserverMetadataReceived metadataReceived;
	};

	class ITorrentStreamObserver
	{
	public:
		virtual ~ITorrentStreamObserver() { }
		virtual void onReadFinished(long streamOffset, const uint8_t *buffer, int64_t offset, int length) { }
		virtual void onReadError(long streamOffset, int error) { }
	};

	struct StreamObserverCallbackSet
	{
		void *context;

		typedef void(CALLCONV*StreamReadCompleted)(void *context, int64_t streamOffset, const uint8_t *data, int data_offset, int data_length);
		typedef void(CALLCONV*StreamReadError)(void *context, int64_t streamOffset, int error);

		StreamReadCompleted readCompleted;
		StreamReadError readError;
	};

	typedef int(CALLCONV *SET_TORRENT_CALLBACKS_PROC)(void *, struct TorrentObserverCallbackSet *callbacks);
	typedef int(CALLCONV *SET_METADATA_CALLBACKS_PROC)(void *, struct TorrentObserverCallbackSet *callbacks);

	// public static IntPtr CreateUniverse(ref UniverseObserverCallbackSet)
	typedef void*(CALLCONV *CREATE_UNIVERSE_PROC)(UniverseObserverCallbackSet *);
	//public static void DestroyUniverse(IntPtr _ucontainer)
	typedef void(CALLCONV *DESTROY_UNIVERSE_PROC)(void*);
	//public static void SetUniverseTargetDir(IntPtr _ucontainer, string target);
	typedef void(CALLCONV *SET_UNIVERSE_TARGET_DIR_PROC)(void *, const wchar_t *);
	//public static void RemoveTorrent(IntPtr _ucontainer, [In, MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.I1, SizeConst = 20)]byte[]infoHash)
    typedef void(CALLCONV *REMOVE_TORRENT_PROC)(void*, const char*);
    //public static void SetExternalIP(IntPtr _ucontainer, [MarshalAs(UnmanagedType.LPWStr)] string val)
    typedef void(CALLCONV *SET_EXTERNAL_IP_PROC)(void*, const char*);

	// public static int CreateMetadataRequest(IntPtr _ucontainer, [MarshalAs(UnmanagedType.LPStr)] string magnetLink, ref IntPtr resultPtr);
	typedef int(CALLCONV *CREATE_METADATA_REQUEST_PROC)(void *, const wchar_t*, void **);
	// public static int DestroyMetadataRequest(IntPtr _mcontainer);
	typedef int(CALLCONV *DESTROY_METADATA_REQUEST_PROC)(void *);

	struct UniverseObserverCallbackSet
	{
		void *context;

		typedef void(CALLCONV*UniverseObserverAddTorrent)(void *context, const char *hash);
		typedef void(CALLCONV*UniverseObserverRemoveTorrent)(void *context, const char *hash);
		typedef void(CALLCONV*UniverseObserverPort)(void *context, int tcpPort, int udpPort);

		UniverseObserverAddTorrent added;
		UniverseObserverRemoveTorrent removed;
		UniverseObserverPort port;
	};

	// public static int SetUniverseCallbacks
	typedef int(CALLCONV *SET_UNIVERSE_CALLBACKS_PROC)(void *, struct UniverseObserverCallbackSet *callbacks);

	// public static int CreateStreamProc(IntPtr _tcontainer, ref StreamObserverCallbackSet, ref IntPtr resultPtr);
	typedef int(CALLCONV *CREATE_STREAM_PROC)(void *_tcontainer, StreamObserverCallbackSet *callbacks, void **resultPtr);
	// public static int DestroyStreamProc(IntPtr _scontainer);
	typedef int(CALLCONV *DESTROY_STREAM_PROC)(void *_scontainer);
	// public static int AddPieceToStream(IntPtr _scontainer, int piece, int priority);
	typedef int(CALLCONV *ADD_PIECE_TO_STREAM_PROC)(void *_scontainer, int piece, int priority);
	// public static int ReleasePieceFromStream(IntPtr _scontainer, int piece);
	typedef int(CALLCONV *RELEASE_PIECE_FROM_STREAM_PROC)(void *_scontainer, int piece);
	// public static int ReadPieceFromStream(IntPtr _scontainer, long streamOffset, int length);
	typedef int(CALLCONV *READ_PIECE_FROM_STREAM_PROC)(void *_scontainer, int64_t streamOffset, int length);

	// public static long GetTorrentLength(IntPtr _tcontainer);
	typedef long(CALLCONV *GET_TORRENT_LENGTH_PROC)(void *);
	// public static int GetTorrentPieceSize(IntPtr _tcontainer);
	typedef int(CALLCONV *GET_TORRENT_PIECE_SIZE_PROC)(void *);
	// public static int GetTorrentInfohash(IntPtr _tcontainer, byte []hash);
	typedef int(CALLCONV *GET_TORRENT_INFOHASH_PROC)(void *, char *);
	// public static bool GetTorrentHavePiece(IntPtr _tcontainer, int piece);
	typedef int(CALLCONV *GET_TORRENT_HAVE_PIECE_PROC)(void *, int);
	// public static int GetNumPieces(IntPtr _tcontainer);
	typedef int(CALLCONV *GET_TORRENT_NUM_PIECES_PROC)(void *);
	// public static void StartTorrent(IntPtr _tcontainer);
	typedef int(CALLCONV *START_TORRENT_PROC)(void *);
	// public static void StopTorrent(IntPtr _tcontainer);
	typedef int(CALLCONV *STOP_TORRENT_PROC)(void *);
	// public static void StartMetadata(IntPtr _mcontainer);
	typedef int(CALLCONV *START_METADATA_PROC)(void *);
	// public static void StopMetadata(IntPtr _mcontainer);
	typedef int(CALLCONV *STOP_METADATA_PROC)(void *);
	
	class TorrentStreamContext
	{
	public:
		TorrentStreamContext(Universe *universe, const std::shared_ptr<Torrent> &torrent);

		void AddObserver(ITorrentStreamObserver *obs);
		void RemoveObserver(ITorrentStreamObserver *obs);

		void RequestPiece(int piece, int deadline);
		void CancelPiece(int piece);
		
		void BeginRead(long streamOffset, int length);

	private:
		static void CALLCONV StreamHavePiece(void *ctx, int piece);
		static void CALLCONV StreamReadCompleted(void *ctx, int64_t streamOffset, const uint8_t *data, int data_offset, int data_length);
		static void CALLCONV StreamReadError(void *ctx, int64_t streamOffset, int error);

		Universe *_universe;
		std::shared_ptr<Torrent> _torrent;
		void *_stream;
		StreamObserverCallbackSet _callbacks;
		std::set<ITorrentStreamObserver*> _observers;

		friend class Torrent;
	};

	class Torrent : public std::enable_shared_from_this<Torrent>
	{
	public:
		void AddObserver(ITorrentEventObserver *obs);
		void RemoveObserver(ITorrentEventObserver *obs);

		SHA1Hash GetInfoHash() const;

		uint32_t GetPieceSize() const;
		uint32_t GetNumPieces() const;

		bool HavePiece(int piece) const;
		uint64_t GetHave() const;

		uint64_t GetLength() const;

		bool HasMetadata() const { return !!_container; }

		void Start();
        void Stop();

		std::shared_ptr<TorrentStreamContext> CreateStreamContext();

		Torrent(Universe *universe);

	private:
		friend class Universe;
		friend class TorrentStreamContext;
		friend class std::shared_ptr < Torrent > ;

		void RefreshCallbacks();
		void TriggerReaped();

		static void CALLCONV MetadataReceived(void *ctx);
		static void CALLCONV PieceCompleted(void *ctx, int piece);
		static void CALLCONV Completed(void *ctx);

		void RetireMetadataSearch(void *torrent_container);

		Universe *_universe;
		void *_metadata;
		void *_container;
		std::set< std::shared_ptr<TorrentStreamContext> > _streams;
		std::set<ITorrentEventObserver*> _observers;
		TorrentObserverCallbackSet _callbacks;
	};

	class IUniverseEventObserver
	{
	public:
		virtual ~IUniverseEventObserver() { }
		virtual void onTorrentAdded(const SHA1Hash &hash) = 0;
		virtual void onTorrentRemoved(const SHA1Hash &hash) = 0;
	};

	class Universe : public std::enable_shared_from_this<Universe>
	{
	public:
		static std::shared_ptr<Universe> Load(const std::wstring &dll);

		void SetDataRoot(const std::wstring &target);

		void AddObserver(IUniverseEventObserver *obs);
		void RemoveObserver(IUniverseEventObserver *obs);
		
		std::shared_ptr<Torrent> LoadTorrent(const std::wstring &torrentFile);
		std::shared_ptr<Torrent> LookupTorrent(const SHA1Hash &hash);
		std::shared_ptr<Torrent> StartMetadata(const std::string &magnetLink);

		void RemoveTorrent(const SHA1Hash &hash);
        typedef std::function<void(std::pair<SHA1Hash, std::shared_ptr<Torrent> >)> each_torrent_callback_t;
        void IterateTorrents(each_torrent_callback_t each_torrent);

		void SetExternalAddress(const std::string &addr);
		int  GetListenPort() const;

	private:
		friend class Torrent;
		friend class TorrentStreamContext;
		friend class std::shared_ptr < Universe > ;

        //TODO: destroy universe
        // ~Universe();

        bool LoadDLL(const std::wstring &dll);

		void MetadataFinished(const char *hash);

		std::map<SHA1Hash, std::shared_ptr<Torrent> > _torrents;
		void *_container;
		std::set<IUniverseEventObserver*> _observers;
		int _tcpPort, _udpPort;
		UniverseObserverCallbackSet _callbacks;

		static void CALLCONV ArgoAddedTorrent(void *ctx, const char *hash);
		static void CALLCONV ArgoRemovedTorrent(void *ctx, const char *hash);
		static void CALLCONV ArgoPort(void *ctx, int tcpPort, int udpPort);

        LOADTORRENTPROC _load_torrent_proc;
		LOOKUP_TORRENT_PROC _lookup_torrent_proc;
		LOOKUP_METADATA_PROC _lookup_metadata_proc;
        CREATE_UNIVERSE_PROC _create_universe_proc;
        DESTROY_UNIVERSE_PROC _destroy_universe_proc;
		SET_UNIVERSE_CALLBACKS_PROC _set_universe_callbacks_proc;
		SET_UNIVERSE_TARGET_DIR_PROC _set_universe_target_dir_proc;
		CREATE_METADATA_REQUEST_PROC _create_metadata_request_proc;
		DESTROY_METADATA_REQUEST_PROC _destroy_metadata_request_proc;
		CREATE_STREAM_PROC _create_stream_proc;
		DESTROY_STREAM_PROC _destroy_stream_proc;
		ADD_PIECE_TO_STREAM_PROC _add_piece_to_stream_proc;
		RELEASE_PIECE_FROM_STREAM_PROC _release_piece_from_stream_proc;
		READ_PIECE_FROM_STREAM_PROC _read_piece_from_stream_proc;
		GET_TORRENT_LENGTH_PROC _get_torrent_length_proc;
		GET_TORRENT_PIECE_SIZE_PROC _get_torrent_piece_size_proc;
		GET_TORRENT_INFOHASH_PROC _get_torrent_infohash_proc;
		GET_TORRENT_HAVE_PIECE_PROC _get_torrent_have_piece_proc;
		GET_TORRENT_NUM_PIECES_PROC _get_torrent_num_pieces_proc;
		START_TORRENT_PROC _start_torrent_proc;
		STOP_TORRENT_PROC _stop_torrent_proc;
		START_METADATA_PROC _start_metadata_proc;
		STOP_METADATA_PROC _stop_metadata_proc;
        REMOVE_TORRENT_PROC _remove_torrent_proc;
		SET_TORRENT_CALLBACKS_PROC _set_torrent_callbacks_proc;
		SET_METADATA_CALLBACKS_PROC _set_metadata_callbacks_proc;
        SET_EXTERNAL_IP_PROC _set_external_ip_proc;
	};
}

#endif//ARGO_LOADER_H_
