@extends('layouts.app')

@section('content')
<div class="list-group container exercises-listing">

    @foreach ($exercises as $exercise)

    <a href="{{ url('/exercise/' . $exercise->id) }}" class="list-group-item list-group-item-action flex-column align-items-start rounded mb-2 pt-3 pl-4">
        <div class="d-flex w-100 justify-content-between">
            <h3 class="mb-1">{{str_limit($exercise->title, 50)}}</h3>
            <p class="mb-1">{{ $exercise->creator_name }}</p>
        </div>
        <div class="d-flex w-100 justify-content-between">
            <h5 style="width: 95% !important">{{ $exercise->description }}</h5>
            @if($exercise->creator_id == Auth::user()->id)
            <form  style="width: 5% !important" method="POST" action="{{ action('Web\ExerciseController@deleteExercise', ['id' => $exercise->id]) }}">
            {{ csrf_field() }}
                <button type="submit" id="remove-button" class="btn btn-danger btn-xs rounded">
                    <i class="far fa-trash-alt"></i>
                </button>
            </form>
            @endif
        </div>
        
    </a>

    @endforeach

    <div class="rounded">
        {{ $exercises->links() }}
    </div>
</div>

@endsection