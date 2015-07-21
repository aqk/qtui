//#include "stdafx.h"
#include <wchar.h>
#include <sstream>
//#include "MagnetURIDesc.h"
#include "ArgoLoader.h"

namespace Argo
{
	void Torrent::MetadataReceived(void *ctx)
	{
		auto torrent = (Torrent *)ctx;
		auto observers = torrent->_observers;
		for (auto it : observers) {
			it->onMetadataReceived();
		}
	}

	void Torrent::PieceCompleted(void *ctx, int piece)
	{
		auto torrent = (Torrent *)ctx;
		auto observers = torrent->_observers;
		for (auto it : observers) {
			it->onPieceCompleted(piece);
		}
	}

	void Torrent::Completed(void *ctx)
	{
		auto torrent = (Torrent *)ctx;
		auto observers = torrent->_observers;
		for (auto it : observers) {
			it->onTorrentCompleted();
		}
	}

	void Torrent::TriggerReaped()
	{
		auto observers = _observers;
		for (auto it : observers) {
			it->onTorrentReaped();
		}
	}
	
	Torrent::Torrent(Universe *universe)
		: _universe(universe), _container(), _metadata()
    {
		_callbacks.context = this;
		_callbacks.metadataReceived = &Torrent::MetadataReceived;
		_callbacks.pieceCompleted = &Torrent::PieceCompleted;
		_callbacks.completed = &Torrent::Completed;
    }

	void Torrent::RefreshCallbacks()
	{
		if (_container) {
			_universe->_set_torrent_callbacks_proc(_container, &_callbacks);
		}
	}

	SHA1Hash Torrent::GetInfoHash() const
	{
		SHA1Hash hash;
		_universe->_get_torrent_infohash_proc(_container, hash.value);
		return hash;
	}

	uint64_t Torrent::GetHave() const
	{
		return 0;
	}

	uint64_t Torrent::GetLength() const
	{
		return _universe->_get_torrent_length_proc(_container);
	}

	void Torrent::RetireMetadataSearch(void *torrent_container)
	{
		_universe->_destroy_metadata_request_proc(_metadata);
		_metadata = nullptr;
		_container = torrent_container;
		auto observers = _observers;
		for (auto it : observers)
		{
			it->onMetadataReceived();
		}
	}

	void Torrent::Start()
	{
		if (_container) {
			_universe->_start_torrent_proc(_container);
		}
		if (_metadata) {
			_universe->_start_metadata_proc(_metadata);
		}
	}

	void Torrent::Stop()
	{
		if (_container) {
			_universe->_stop_torrent_proc(_container);
		}
		if (_metadata) {
			_universe->_stop_metadata_proc(_container);
		}
	}

	uint32_t Torrent::GetPieceSize() const
	{
		return _universe->_get_torrent_piece_size_proc(_container);
	}

	uint32_t Torrent::GetNumPieces() const
	{
		return _universe->_get_torrent_num_pieces_proc(_container);
	}

	bool Torrent::HavePiece(int piece) const
	{
		return _universe->_get_torrent_have_piece_proc(_container, piece);
	}

	void Torrent::AddObserver(ITorrentEventObserver *obs)
	{
		_observers.insert(obs);
	}

	void Torrent::RemoveObserver(ITorrentEventObserver *obs)
	{
		_observers.erase(obs);
	}

	std::shared_ptr<TorrentStreamContext> Torrent::CreateStreamContext()
	{
		auto stream = std::make_shared<TorrentStreamContext>(_universe, shared_from_this());
		if (stream->_stream) {
			_streams.insert(stream);
			return stream;
		} else {
			return std::shared_ptr<TorrentStreamContext>();
		}
	}

	void TorrentStreamContext::StreamReadCompleted(void *ctx, int64_t streamOffset, const uint8_t *data, int data_offset, int data_length)
	{
		auto observers = ((TorrentStreamContext*)ctx)->_observers;
		for (auto it : observers) {
			it->onReadFinished(streamOffset, data, data_offset, data_length);
		}
	}

	void TorrentStreamContext::StreamReadError(void *ctx, int64_t streamOffset, int error)
	{
		auto observers = ((TorrentStreamContext*)ctx)->_observers;
		for (auto it : observers) {
			it->onReadError(streamOffset, error);
		}
	}

	TorrentStreamContext::TorrentStreamContext(Universe *universe, const std::shared_ptr<Torrent> &torrent) : 
		_universe(universe), 
		_torrent(torrent) {
		_callbacks.context = this;
		_callbacks.readCompleted = &TorrentStreamContext::StreamReadCompleted;
		_callbacks.readError = &TorrentStreamContext::StreamReadError;

		_universe->_create_stream_proc(torrent->_container, &_callbacks, &_stream);
	}

	void TorrentStreamContext::AddObserver(ITorrentStreamObserver *obs)
	{
		_observers.insert(obs);
	}

	void TorrentStreamContext::RemoveObserver(ITorrentStreamObserver *obs)
	{
		_observers.erase(obs);
	}

	void TorrentStreamContext::RequestPiece(int piece, int deadline)
	{
		_universe->_add_piece_to_stream_proc(_stream, piece, deadline);
	}

	void TorrentStreamContext::CancelPiece(int piece)
	{
		_universe->_release_piece_from_stream_proc(_stream, piece);
	}

	void TorrentStreamContext::BeginRead(long streamOffset, int length)
	{
		_universe->_read_piece_from_stream_proc(_stream, streamOffset, length);
	}

	void Universe::AddObserver(IUniverseEventObserver *obs)
	{
		_observers.insert(obs);
	}

	void Universe::RemoveObserver(IUniverseEventObserver *obs)
	{
		_observers.erase(obs);
	}

	std::shared_ptr<Universe> Universe::Load(const std::wstring &dll)
	{
        std::shared_ptr<Universe> universe(new Universe);
        if (universe->LoadDLL(dll)) {
            return universe;
        }
        return std::shared_ptr<Universe>();
	}

	void Universe::SetDataRoot(const std::wstring &target)
	{
		_set_universe_target_dir_proc(_container, target.c_str());
	}

	void Universe::ArgoAddedTorrent(void *ctx, const char *hash)
	{
		auto observers = ((Universe*)ctx)->_observers;
		for (auto it : observers) {
			it->onTorrentAdded(SHA1Hash(hash));
		}
	}

	void Universe::ArgoRemovedTorrent(void *ctx, const char *hash)
	{
		auto observers = ((Universe*)ctx)->_observers;
		for (auto it : observers) {
			it->onTorrentRemoved(SHA1Hash(hash));
		}
	}

	void Universe::ArgoPort(void *ctx, int tcpPort, int udpPort)
	{
		((Universe*)ctx)->_tcpPort = tcpPort;
		((Universe*)ctx)->_udpPort = udpPort;
	}

    bool Universe::LoadDLL(const std::wstring &dll)
    {
        HMODULE argo_module = LoadLibrary(dll.c_str());
        if (argo_module == NULL) {
            return false;
        }

        _load_torrent_proc =
            (LOADTORRENTPROC)GetProcAddress(argo_module, "LoadTorrent");
        if (_load_torrent_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _create_universe_proc =
            (CREATE_UNIVERSE_PROC)GetProcAddress(argo_module, "CreateUniverse");
        if (_create_universe_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _destroy_universe_proc =
            (DESTROY_UNIVERSE_PROC)GetProcAddress(argo_module, "DestroyUniverse");
        if (_destroy_universe_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _remove_torrent_proc =
            (REMOVE_TORRENT_PROC)GetProcAddress(argo_module, "RemoveTorrent");
        if (_remove_torrent_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _set_external_ip_proc =
            (SET_EXTERNAL_IP_PROC)GetProcAddress(argo_module, "SetExternalIP");
        if (_set_external_ip_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _create_metadata_request_proc =
            (CREATE_METADATA_REQUEST_PROC)GetProcAddress(argo_module, "CreateMetadataRequest");
        if (_create_metadata_request_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _destroy_metadata_request_proc =
            (DESTROY_METADATA_REQUEST_PROC)GetProcAddress(argo_module, "DestroyMetadataRequest");
        if (_destroy_metadata_request_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _get_torrent_length_proc =
            (GET_TORRENT_LENGTH_PROC)GetProcAddress(argo_module, "GetTorrentLength");
        if (_get_torrent_length_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _get_torrent_infohash_proc =
            (GET_TORRENT_INFOHASH_PROC)GetProcAddress(argo_module, "GetTorrentInfoHash");
        if (_get_torrent_infohash_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _start_torrent_proc =
            (START_TORRENT_PROC)GetProcAddress(argo_module, "StartTorrent");
        if (_start_torrent_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _start_metadata_proc =
            (START_TORRENT_PROC)GetProcAddress(argo_module, "StartMetadata");
        if (_start_metadata_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _set_torrent_callbacks_proc =
            (SET_TORRENT_CALLBACKS_PROC)GetProcAddress(argo_module, "SetTorrentCallbacks");
        if (_set_torrent_callbacks_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _set_metadata_callbacks_proc =
            (SET_METADATA_CALLBACKS_PROC)GetProcAddress(argo_module, "SetMetadataCallbacks");
        if (_set_metadata_callbacks_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _lookup_torrent_proc =
            (LOOKUP_TORRENT_PROC)GetProcAddress(argo_module, "LookupTorrent");
        if (_lookup_torrent_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _lookup_metadata_proc =
            (LOOKUP_METADATA_PROC)GetProcAddress(argo_module, "LookupMetadata");
        if (_lookup_metadata_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _set_universe_target_dir_proc =
            (SET_UNIVERSE_TARGET_DIR_PROC)GetProcAddress(argo_module, "SetTargetDirectory");
        if (_set_universe_target_dir_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _get_torrent_have_piece_proc =
            (GET_TORRENT_HAVE_PIECE_PROC)GetProcAddress(argo_module, "GetTorrentHavePiece");
        if (_get_torrent_have_piece_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _create_stream_proc =
            (CREATE_STREAM_PROC)GetProcAddress(argo_module, "CreateStream");
        if (_create_stream_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _add_piece_to_stream_proc =
            (ADD_PIECE_TO_STREAM_PROC)GetProcAddress(argo_module, "AddPieceToStream");
        if (_add_piece_to_stream_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _release_piece_from_stream_proc =
            (RELEASE_PIECE_FROM_STREAM_PROC)GetProcAddress(argo_module, "ReleasePieceFromStream");
        if (_release_piece_from_stream_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _read_piece_from_stream_proc =
            (READ_PIECE_FROM_STREAM_PROC)GetProcAddress(argo_module, "ReadFromStream");
        if (_read_piece_from_stream_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _get_torrent_num_pieces_proc =
            (GET_TORRENT_NUM_PIECES_PROC)GetProcAddress(argo_module, "GetTorrentNumPieces");
        if (_get_torrent_num_pieces_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }
        _get_torrent_piece_size_proc =
            (GET_TORRENT_PIECE_SIZE_PROC)GetProcAddress(argo_module, "GetTorrentPieceSize");
        if (_get_torrent_piece_size_proc == NULL) {
            FreeLibrary(argo_module);
            return false;
        }

        _callbacks.context = this;
        _callbacks.added = &ArgoAddedTorrent;
        _callbacks.removed = &ArgoRemovedTorrent;
        _callbacks.port = &ArgoPort;

        _container = _create_universe_proc(&_callbacks);
        return true;
    }

#if 0
	std::shared_ptr<Torrent> Universe::StartMetadata(const std::string &magnetLink)
	{
		MagnetURIDesc desc(magnetLink.c_str());
		if (!desc.success) {
			return std::shared_ptr<Torrent>();
		}
		auto it = _torrents.find(desc.infohash);
		if (it != _torrents.end()) {
			return it->second;
		}
		std::shared_ptr<Torrent> torrent(new Torrent(this));
		std::wostringstream wideMagnetLinkAccum;
		wideMagnetLinkAccum << magnetLink.c_str();

		int res = _create_metadata_request_proc(_container, wideMagnetLinkAccum.str().c_str(), &torrent->_metadata);
		if (res != 0)
		{
			torrent.reset();
		}
		else
		{
			_torrents[desc.infohash] = torrent;
			torrent->RefreshCallbacks();
		}
		return torrent;
	}
#endif
	std::shared_ptr<Torrent> Universe::LoadTorrent(const std::wstring &torrentFile)
	{
        std::shared_ptr<Torrent> torrent(new Torrent(this));
        int res = _load_torrent_proc(_container, torrentFile.c_str(), &torrent->_container);
		if (res != 0)
		{
			torrent.reset();
		}
		else
		{
			SHA1Hash hash;
			_get_torrent_infohash_proc(torrent->_container, hash.value);
			torrent->RefreshCallbacks();
		}
		return torrent;
	}

	std::shared_ptr<Torrent> Universe::LookupTorrent(const SHA1Hash &hash)
	{
		auto it = _torrents.find(hash);
		if (it != _torrents.end())
		{
			return it->second;
		}
		void *tcontainer;
		int res = _lookup_torrent_proc(_container, hash.value, &tcontainer);
		if (res == 0) {
			auto torrent = std::make_shared<Torrent>(this);
			torrent->_container = tcontainer;
			return torrent;
		} else {
			res = _lookup_metadata_proc(_container, hash.value, &tcontainer);
			if (res == 0) {
				auto torrent = std::make_shared<Torrent>(this);
				torrent->_metadata = tcontainer;
				return torrent;
			}
		}
		return std::shared_ptr<Torrent>();
	}

	void Universe::RemoveTorrent(const SHA1Hash &hash)
	{
		auto torrent_it = _torrents.find(hash);
		if (torrent_it == _torrents.end()) {
			return;
		}
		torrent_it->second->TriggerReaped();
		_torrents.erase(torrent_it);
        _remove_torrent_proc(_container, hash.value);
	}

	void Universe::SetExternalAddress(const std::string &addr)
	{
        _set_external_ip_proc(_container, addr.c_str());
	}

	int  Universe::GetListenPort() const
	{
		return _tcpPort;
	}

}
