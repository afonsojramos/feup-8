@extends('layouts.app')

@section('content')

<div class="list-group container exercises-listing">

    @foreach ($exercises as $exercise)

    <a href="{{ url('/exercise/' . $exercise->id) }}" class="list-group-item list-group-item-action flex-column align-items-start rounded mb-2 pt-3 pl-4">
        <div class="d-flex w-100 justify-content-between">
            <h3 class="mb-1">{{str_limit($exercise->title, 50)}}</h3>
            <form method="POST" style="margin-top:2%;" action="{{ action('Web\ExerciseController@deleteExercise', ['id' => $exercise->id]) }}">
            {{ csrf_field() }}
                <button type="submit" id="remove-button" class="btn btn-danger btn-xs rounded">
                    <img src="/images/remove.png" alt="remove" height="20" width="20">
                </button>
            </form>
        </div>
        <h5>{{ $exercise->description }}</h5>
    </a>

    @endforeach

    <div class="rounded">
        {{ $exercises->links() }}
    </div>
</div>

@endsection
